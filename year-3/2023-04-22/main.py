import psycopg2 as psql
import pygame as pg
from random import randint
from copy import copy
WIDTH = 384
HEIGHT = 240
BSIZE = 38
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)

class Item:
  def __init__(self, id: int, name: str, image: str, amount: int = 1, stackable: bool = True) -> None:
    self.id = id
    self.name = name
    self.surface = pg.image.load(f'./assets/{image}')
    self.box = self.surface.get_rect()
    self.amount = amount if stackable else 1
    self.stackable = stackable
  
  def draw(self, position: list[int] or tuple[int]) -> None:
    dx, dy = position[0] - self.box.left, position[1] - self.box.top
    self.box.move_ip(dx + 3, dy + 3)
    screen.blit(self.surface, self.box)
    if self.stackable and self.amount > 1:
      text = font.render(str(self.amount), True, BLACK)
      text_box = text.get_rect(right = self.box.right, bottom = self.box.bottom + 5)
      screen.blit(text, text_box)

class Slot:
  def __init__(self, index: int, box: pg.Rect) -> None:
    self.index = index
    self.box = box
    self.item = None

  def __str__(self) -> str:
    return f'<Slot({self.index})>'

  def put(self, item: Item) -> int:
    if self.item != None:
      if self.item.id == item.id and self.item.stackable:
        self.item.amount += item.amount
        return 2
      else: return 0
    self.item = item
    return 1

  def take(self) -> Item or None:
    if self.item == None: return
    _i = self.item
    self.item = None
    return _i

class Inventory:
  def __init__(self, rows: int, columns: int) -> None:
    self.rows = rows
    self.columns = columns
    self.slots = []
    self.items = []
    self.__init_slots(rows, columns)

  def __init_slots(self, rows: int, columns: int) -> None:
    index = 0
    for row in range(rows):
      for col in range(columns):
        slot = Slot(index, pg.Rect(col * BSIZE + 2, HEIGHT - (row + 1) * BSIZE - 2, BSIZE, BSIZE))
        self.slots.append(slot)
        index += 1

  def draw(self):
    for slot in self.slots:
      pg.draw.rect(screen, BLACK, slot.box, width = 1)
      if slot.item != None: slot.item.draw(slot.box)

  def get_slot_by_position(self, position: list[int] or tuple[int]) -> Slot or None:
    for slot in self.slots:
      if slot.box.left <= position[0] <= slot.box.right and slot.box.top <= position[1] <= slot.box.bottom:
        return slot

  def get_slot_by_index(self, index: int) -> Slot or None:
    try: return self.slots[index]
    except IndexError: return None

  def add(self, slot: int, item: Item) -> bool:
    _s = self.get_slot_by_index(slot)
    if _s == None: return False
    if _s.take() != None: return False
    _s.put(item)
    return True

class App:
  def __init__(self) -> None:
    self.drag_item = None
    self.drag_parent_slot = None

  def handle_motion(self, event):
    screen.fill(WHITE)
    inventory.draw()
    if self.drag_item == None: self.show_name(event)
    else:
      self.drag_item.draw(event.pos)
    pg.display.flip()

  def handle_click(self, event):
    slot = inventory.get_slot_by_position(event.pos)
    if slot == None: return
    if event.button == 1: self.__handle_left_click(slot)
    elif event.button == 3: self.__handle_right_click(slot)
    screen.fill(WHITE)
    inventory.draw()
    self.show_name(event)
    if self.drag_item: self.drag_item.draw(event.pos)
    pg.display.flip()

  def show_name(self, event):
    slot = inventory.get_slot_by_position(event.pos)
    if slot == None or slot.item == None:
      pg.draw.rect(screen, WHITE, (0, 0, WIDTH, 20))
      pg.display.flip()
      return
    text = font_header.render(slot.item.name, True, BLACK)
    text_box = text.get_rect(center = (WIDTH / 2, 20))
    screen.blit(text, text_box)

  def __handle_left_click(self, slot: Slot):
    if self.drag_item:
      _t = slot.put(self.drag_item)
      if _t == 1:
        if app.drag_parent_slot == None:
          cursor.execute(f'insert into contents.inventory values ({slot.index}, {self.drag_item.id}, {self.drag_item.amount}); commit;')
        else:
          cursor.execute(f'update contents.inventory set slot = {slot.index} where slot = {self.drag_parent_slot.index}; commit;')
        self.drag_item = None
        self.drag_parent_slot = None
      elif _t == 2:
        cursor.execute(f'update contents.inventory set amount = {slot.item.amount} where slot = {slot.index};')
        cursor.execute(f'delete from contents.inventory where slot = {self.drag_parent_slot.index}; commit;')
        self.drag_item = None
        self.drag_parent_slot = None
      else:
        _i = slot.take()
        slot.put(self.drag_item)
        if self.drag_parent_slot != None:
          cursor.execute(f'update contents.inventory set item = {self.drag_item.id}, amount = {self.drag_item.amount} where slot = {slot.index};')
          cursor.execute(f'update contents.inventory set item = {_i.id}, amount = {_i.amount} where slot = {self.drag_parent_slot.index}; commit;')
        else:
          cursor.execute(f'update contents.inventory set item = {self.drag_item.id}, amount = {self.drag_item.amount} where slot = {slot.index};')
          empty = 0
          for i in range(30):
            if inventory.get_slot_by_index(i).item != None: continue
            empty = i
            break
          if inventory.get_slot_by_index(empty): empty = -1
          if empty >= 0:
            cursor.execute(f'insert into contents.inventory values ({empty}, {_i.id}, {_i.amount}); commit;')
        self.drag_item = _i
    else:
      if slot.item == None: return
      item = slot.take()
      if item == None: return
      self.drag_item = item
      self.drag_parent_slot = slot

  def __handle_right_click(self, slot: Slot):
    if slot.item == None: return
    if not slot.item.stackable: return
    if self.drag_item:
      if self.drag_item.name != slot.item.name: return
      self.drag_item.amount += 1
    else:
      self.drag_item = copy(slot.item)
      self.drag_item.amount = 1
    slot.item.amount -= 1
    cursor.execute(f'update contents.inventory set amount = amount - 1 where slot = {slot.index}; commit;')
    if slot.item.amount == 0:
      slot.item = None
      cursor.execute(f'delete from contents.inventory where slot = {slot.index};')

db = psql.connect(dbname = 'python', user = 'client', password = 'qwerty12345', host = 'localhost')
cursor = db.cursor()

pg.init()
pg.display.set_caption('Inventory')
pg.display.set_icon(pg.image.load('./assets/terra_blade.png'))
screen = pg.display.set_mode([WIDTH, HEIGHT])
screen.fill(WHITE)

app = App()
running = True
clock = pg.time.Clock()

font = pg.font.Font('./assets/andy.ttf', 16)
font_header = pg.font.Font('./assets/andy.ttf', 22)
font.set_bold(True)
font_header.set_bold(True)

ROWS = 3
COLUMNS = (WIDTH - 4) // BSIZE
inventory = Inventory(ROWS, COLUMNS)
cursor.execute('select exists (select * from contents.inventory limit 1);')
inv_state = cursor.fetchone()
if inv_state[0] == True:
  cursor.execute('select slot, id, title, image, amount, stackable from contents.inventory inv inner join contents.items itm on itm.id = inv.item;')
  for entry in cursor.fetchall():
    inventory.add(entry[0], Item(*entry[1:]))
else:
  cursor.execute('select * from contents.items;')
  for entry in cursor.fetchall():
    slot = randint(0, 29)
    while inventory.get_slot_by_index(slot).item != None: slot = randint(0, 29)
    amt = randint(1, entry[4])
    inventory.add(slot, Item(id = entry[0], name = entry[1], image = entry[2], stackable = entry[3], amount = amt))
    cursor.execute(f'insert into contents.inventory values ({slot}, {entry[0]}, {amt});')
inventory.draw()
pg.display.flip()

while running:
  for event in pg.event.get():
    if event.type == pg.MOUSEBUTTONUP: app.handle_click(event)
    if event.type == pg.MOUSEMOTION: app.handle_motion(event)
    if event.type == pg.QUIT: running = False
  clock.tick(25)
db.close()

import pygame as pg
from random import randint
from copy import copy
WIDTH = 384
HEIGHT = 240
BSIZE = 38
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)

class Item:
  def __init__(self, name: str, image: str, amount: int = 1, stackable: bool = True) -> None:
    self.name = name
    self.surface = pg.image.load(image)
    self.box = self.surface.get_rect()
    self.amount = amount if stackable else None
    self.stackable = stackable
  
  def draw(self, position: list[int] or tuple[int]) -> None:
    dx, dy = position[0] - self.box.left, position[1] - self.box.top
    self.box.move_ip(dx + 3, dy + 3)
    screen.blit(self.surface, self.box)
    if self.amount != None and self.amount > 1:
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

  def put(self, item: Item) -> bool:
    if self.item != None:
      if self.item.name == item.name:
        self.item.amount += item.amount
        return True
      else: return False
    self.item = item
    return True

  def take(self) -> Item or None:
    if self.item == None: return True
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

class App:
  def __init__(self) -> None: pass

  def handle_motion(self, event):
    screen.fill(WHITE)
    inventory.draw()
    if drag_item == None: self.show_name(event)
    else:
      drag_item.draw(event.pos)
    pg.display.flip()

  def handle_click(self, event):
    global drag_item
    slot = inventory.get_slot_by_position(event.pos)
    if slot == None: return
    if event.button == 1: self.__handle_left_click(slot)
    elif event.button == 3: self.__handle_right_click(slot)
    screen.fill(WHITE)
    inventory.draw()
    self.show_name(event)
    if drag_item: drag_item.draw(event.pos)
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
    global drag_item
    if drag_item:
      if slot.put(drag_item): drag_item = None
      else:
        _i = slot.take()
        slot.put(drag_item)
        drag_item = _i
    else:
      if slot.item == None: return
      item = slot.take()
      if item == None: return
      drag_item = item

  def __handle_right_click(self, slot: Slot):
    global drag_item
    if slot.item == None: return
    if not slot.item.stackable: return
    if drag_item:
      if drag_item.name != slot.item.name: return
      drag_item.amount += 1
    else:
      drag_item = copy(slot.item)
      drag_item.amount = 1
    slot.item.amount -= 1
    if slot.item.amount == 0: slot.item = None

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
inventory.get_slot_by_index(randint(0, ROWS * COLUMNS - 1)).put(Item('Iron Sword', './assets/sword.png', stackable = False))
inventory.get_slot_by_index(randint(0, ROWS * COLUMNS - 1)).put(Item('Wooden Bow', './assets/bow.png', stackable = False))
inventory.get_slot_by_index(randint(0, ROWS * COLUMNS - 1)).put(Item('Wooden Arrow', './assets/arrow.png', randint(1, 200)))
inventory.get_slot_by_index(randint(0, ROWS * COLUMNS - 1)).put(Item('Lesser Healing Potion', './assets/potion.png', randint(1, 20)))
inventory.get_slot_by_index(randint(0, ROWS * COLUMNS - 1)).put(Item('Gold Ore', './assets/gold_ore.png', randint(1, 100)))
inventory.get_slot_by_index(randint(0, ROWS * COLUMNS - 1)).put(Item('Stone Block', './assets/stone.png', randint(1, 999)))
inventory.get_slot_by_index(randint(0, ROWS * COLUMNS - 1)).put(Item('Torch', './assets/torch.png', randint(1, 200)))
inventory.get_slot_by_index(randint(0, ROWS * COLUMNS - 1)).put(Item('Gel', './assets/gel.png', randint(1, 200)))
inventory.draw()
pg.display.flip()

drag_item = None
while running:
  for event in pg.event.get():
    if event.type == pg.MOUSEBUTTONUP: app.handle_click(event)
    if event.type == pg.MOUSEMOTION: app.handle_motion(event)
    if event.type == pg.QUIT: running = False
  clock.tick(25)

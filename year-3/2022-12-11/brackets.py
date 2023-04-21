def check(string: str) -> int:
    brks = []
    posn = []

    pairs = { '(': ')', '[': ']', '{': '}' }
    opening = ['(', '[', '{']
    closing = [')', ']', '}']
    allowed = opening + closing
    indices = range(len(string))
    for i in indices:
        char = string[i]
        if char not in allowed: continue  # пропускаем все, кроме скобок

        if len(brks) and char == pairs[brks[0]]:  # убираем из стека, если есть пара
            brks.pop(0)
            posn.pop(0)
        elif char in closing:  # это закрывающая скобка, но без пары к последней открытой
            # заканчиваем обход и возвращаем ее индекс
            return i + 1
        else:
            brks.insert(0, char)
            posn.insert(0, i + 1)
    if len(brks):
        return posn.pop()
    else: return 0


s = input()
# s = '(' * 20000 + ')' * 20000  <-- тест производительности
r = check(s)
if (r == 0): print('Success')
else: print(r)
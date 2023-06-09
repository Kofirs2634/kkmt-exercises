# Инвентарь с БД на Pygame
| Курс | Язык | Версия | Тема | Дата
|:-:|:-:|:-:|:-:|:-:|
| 3 | `Python` | 3.11 | Работа с БД | 18 апреля 2023 |

Простейший инвентарь с использованием Python-библиотеки для создания игр "Pygame". Механика, шрифты и спрайты получены из текстурпака "HD Textures" для игры-песочницы Terraria.

При запуске, если инвентарь пуст, создается набор предметов в случайном количестве в случайных слотах. Всего в инвентаре доступно 30 слотов (три ряда по десять). Возможные взаимодействия:
+ **Клик:** берет стопку предметов для переноса. После этого...
  + ...клик на **пустом** слоте кладет стопку предметов;
  + ...клик на **занятом** слоте поменяем предметы местами.
+ **Правый клик:** берет один предмет из стопки. Если в стопке всего один предмет, забирает все.
+ При сложении стопок одинаковых предметов они сливаются в одну.
+ При наведении курсора наверху экрана показывается название предмета. Не работает при переносе стопок.

Любое взаимодействие с инвентарем сохраняется в базе данных. Используемый диалект — PostgreSQL версии 15. База имеет название `python` и хостится локально на порте `5432`. Запросы производятся через пользователя `client`.

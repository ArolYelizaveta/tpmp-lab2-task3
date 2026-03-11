# Протокол тестирования программы (вариант 16)

## 1. Цель тестирования
Проверить корректность работы всех функций программы: ввод/вывод, сортировка, поиск товаров с истекающим сроком, подсчёт по производителям, поиск товара с макс. ценой.

## 2. Методика тестирования
Использовались тестовые данные, встроенные в программу (запуск с аргументом `test`). Тестовый набор включает 12 записей с различными датами, ценами и производителями.

## 3. Ожидаемые результаты
- Сортировка по дате производства должна упорядочить записи от самой ранней даты к самой поздней.
- Товары с истекающим сроком: должны отобразиться те, у которых разница между сроком годности и текущей датой составляет от 0 до 2 дней (включительно).
- Подсчёт по производителям: должны быть просуммированы количества товаров одинаковых производителей.
- Товар с макс. ценой (не просрочен): должен быть найден корректно; если все просрочены — выводится сообщение.

## 4. Входные данные (тестовый набор)
№	Name	 Price Production date Expiration date Quantity	Manufacturer
1	Milk	  1.5	2025-01-10	     2025-03-10	      10	    Grandma's Jar
2	Bread 0.8	2025-01-12	     2025-02-12	      20	    Bakery No.1
3	Cheese 3.2	2025-01-05	     2025-03-05	       5 	Cheese House
| ... (полный список из 12 позиций) |

## 5. Фактические результаты (вывод программы)
Test mode: using predefined data.

=== Initial product list ===
Name: Milk
Price: 1.50
Production date: 2025-01-10
Expiration date: 2025-03-10
Quantity: 10
Manufacturer: Grandma's Jar
----------------------
Name: Bread
Price: 0.80
Production date: 2025-01-12
Expiration date: 2025-02-12
Quantity: 20
Manufacturer: Bakery No.1
----------------------
Name: Cheese
Price: 3.20
Production date: 2025-01-05
Expiration date: 2025-03-05
Quantity: 5
Manufacturer: Cheese House
----------------------
Name: Sausage
Price: 5.00
Production date: 2025-01-08
Expiration date: 2025-02-08
Quantity: 7
Manufacturer: Meat Yard
----------------------
Name: Yogurt
Price: 0.90
Production date: 2025-01-15
Expiration date: 2025-03-01
Quantity: 15
Manufacturer: Dairy World
----------------------
Name: Juice
Price: 2.10
Production date: 2025-01-07
Expiration date: 2025-04-07
Quantity: 12
Manufacturer: Fruit Garden
----------------------
Name: Cookies
Price: 1.20
Production date: 2025-01-20
Expiration date: 2025-05-20
Quantity: 8
Manufacturer: Sweet Tooth
----------------------
Name: Chocolate
Price: 2.50
Production date: 2025-01-18
Expiration date: 2025-06-18
Quantity: 6
Manufacturer: Confectioner
----------------------
Name: Butter
Price: 2.80
Production date: 2025-01-09
Expiration date: 2025-02-09
Quantity: 4
Manufacturer: Butter Factory
----------------------
Name: Kefir
Price: 1.10
Production date: 2025-01-14
Expiration date: 2025-03-14
Quantity: 9
Manufacturer: Dairy World
----------------------
Name: Cottage cheese
Price: 1.90
Production date: 2025-01-11
Expiration date: 2025-02-11
Quantity: 3
Manufacturer: Dairy World
----------------------
Name: Waffles
Price: 1.30
Production date: 2025-01-13
Expiration date: 2025-03-13
Quantity: 11
Manufacturer: Sweet Tooth
----------------------

=== After sorting by production date (ascending) ===
Name: Cheese
Price: 3.20
Production date: 2025-01-05
Expiration date: 2025-03-05
Quantity: 5
Manufacturer: Cheese House
----------------------
Name: Juice
Price: 2.10
Production date: 2025-01-07
Expiration date: 2025-04-07
Quantity: 12
Manufacturer: Fruit Garden
----------------------
Name: Sausage
Price: 5.00
Production date: 2025-01-08
Expiration date: 2025-02-08
Quantity: 7
Manufacturer: Meat Yard
----------------------
Name: Butter
Price: 2.80
Production date: 2025-01-09
Expiration date: 2025-02-09
Quantity: 4
Manufacturer: Butter Factory
----------------------
Name: Milk
Price: 1.50
Production date: 2025-01-10
Expiration date: 2025-03-10
Quantity: 10
Manufacturer: Grandma's Jar
----------------------
Name: Cottage cheese
Price: 1.90
Production date: 2025-01-11
Expiration date: 2025-02-11
Quantity: 3
Manufacturer: Dairy World
----------------------
Name: Bread
Price: 0.80
Production date: 2025-01-12
Expiration date: 2025-02-12
Quantity: 20
Manufacturer: Bakery No.1
----------------------
Name: Waffles
Price: 1.30
Production date: 2025-01-13
Expiration date: 2025-03-13
Quantity: 11
Manufacturer: Sweet Tooth
----------------------
Name: Kefir
Price: 1.10
Production date: 2025-01-14
Expiration date: 2025-03-14
Quantity: 9
Manufacturer: Dairy World
----------------------
Name: Yogurt
Price: 0.90
Production date: 2025-01-15
Expiration date: 2025-03-01
Quantity: 15
Manufacturer: Dairy World
----------------------
Name: Chocolate
Price: 2.50
Production date: 2025-01-18
Expiration date: 2025-06-18
Quantity: 6
Manufacturer: Confectioner
----------------------
Name: Cookies
Price: 1.20
Production date: 2025-01-20
Expiration date: 2025-05-20
Quantity: 8
Manufacturer: Sweet Tooth
----------------------

=== Products expiring soon (within 2 days) ===
No such products.

=== Product quantities by manufacturer ===
Cheese House: 5 pcs.
Fruit Garden: 12 pcs.
Meat Yard: 7 pcs.
Butter Factory: 4 pcs.
Grandma's Jar: 10 pcs.
Dairy World: 27 pcs.
Bakery No.1: 20 pcs.
Sweet Tooth: 19 pcs.
Confectioner: 6 pcs.

=== Product with maximum price (not expired) ===
No products with unexpired shelf life.


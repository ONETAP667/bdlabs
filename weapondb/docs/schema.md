# ERD
![ERD](/docs/weapondb-plantuml.png "ERD.")
# Опис Таблиць

### Users
  
**Призначення:** Зберігає інформацію про облікові записи користувачів.

| Стовпець | Тип | Обмеження | Опис |
|----------|-----|-----------|------|
| ID | SERIAL | PRIMARY KEY | Унікальний ID користувача|
| Username | varchar(256) | NOT NULL | Ім'я користувача|
| Balance | integer  | NOT NULL DEFAULT 0 | Баланс користувача в центах|
| DateJoined| timestamptz | NOT NULL DEFAULT now() | Дата створення акаунту користувача|
| RestrictionType| integer | REFERENCES "RestrictionType"("ID") DEFAULT 0 | Тип обмеження користувача
| RestrictedUntil | timestamptz | - | До коли обмежено користувача|
| RestrictionReason | varchar(256) | - | Причина обмеження користувача|
| Archive | BOOLEAN  | DEFAULT FALSE | Чи активний акаунт користувача|
| Version| integer | DEFAULT 0 | Використовується для оптимістичного блокування |

**Зв'язки:**
- Один-до-одного з `RestrictionType` (користувач може мати один тип обмеження)
- Один-до-багатьох з `Items` (користувач може мати кілька предметів)
- Один-до-багатьох з `Transactions` (користувач може мати кілька транзакцій)

### Items
  
**Призначення:** Зберігає інформацію про предмети користувачів.

| Стовпець | Тип | Обмеження | Опис |
|----------|-----|-----------|------|
| ID | SERIAL | PRIMARY KEY | Унікальний ID предмета|
| OwnerID | integer| NOT NULL REFERENCES "Users" ("ID") | ID власника|
| Price | integer|  NOT NULL DEFAULT 0 CHECK ("Price" >= 0), | Ціна предмета |0
| Type | integer|  REFERENCES "ItemTypes" ("TypeID") | Тип предмета |
| Weapon | integer|  DEFAULT NULL REFERENCES "WeaponIDToWeapon"("WeaponID") | Тип зброї, якщо це зброя |
| Special | integer|  DEFAULT NULL REFERENCES "SpecialToCategory"("SpecialID") | Спеціальні властивості предмета |
| SkinID | integer|  NOT NULL DEFAULT 0 | Текстура предмета в грі |
| Float| double precision |  NOT NULL DEFAULT 0.0 CHECK ("Float" >= 0.0) | Наскільки поношений предмет |
| Pattern| integer|  NOT NULL DEFAULT 0 CHECK ("Pattern" >= 0)| Як текстура накладається на предмет у грі |
| Nametag| varchar(256) | - | Ім'я предмету |
| Charm| integer|  - | Нанесений брелок на зброю |
| Charm Pattern| integer|  - | Pattern брелка на зброї |
| DateCreated"| timestamptz | NOT NULL DEFAULT now() | Дата створення предмету|

**Індекси**:
- `idx_items_owner` на `"OwnerID"`, для пошуку предметів за власником
-  `idx_items_type ` на `"Type"`, для пошуку предметів за типом

**Зв'язки:**
- Один-до-одного з `"Users"` (Предмет може мати одного власника)
- Один-до-багатьох з `"Transactions"` (Предмет може брати участь у декількох транзакціях)
- Один-до-одного з `"ItemPreviews"` (Предмет може мати один Preview)
- Один-до-одного з `"ItemTypes"` (Предмет може мати один тип )
- Один-до-одного з `"WeaponIDToWeapon"` (Предмет може мати один вид зброї)
- Один-до-одного з `"ItemType"` (Предмет може мати один вид)
- Один-до-одного з `"SpecialToCategory"` (Предмет може мати одну спеціальну властивість)
- Один-до-багатьох з `"StickersOnWeapon"` (Предмет може мати декілька наліпок)

### Transactions
  
**Призначення:** Зберігає інформацію про транзакції між користувачами.

| Стовпець | Тип | Обмеження | Опис |
|----------|-----|-----------|------|
| TransactionID | SERIAL | PRIMARY KEY | Унікальний ID транзакції |
| SellerID | integer|  REFERENCES "Users" ("ID") | ID продавця |
| BuyerID | integer|  REFERENCES "Users" ("ID") | ID покупця |
| ItemID | integer|  REFERENCES "Items" ("ID") | ID предмета |
| Price | integer|  NOT NULL | Ціна предмету |
| Canceled| BOOLEAN | DEFAULT false | Чи відмінено транзакцію |
| Archive | BOOLEAN | DEFAULT FALSE | Чи архівовано транзакцію |

**Індекси**:
- `idx_transactions_buyer ` на `"BuyerID"`, для пошуку транзакцій покупця
- `idx_transactions_seller ` на `"SellerID"`, для пошуку транзакцій продавця

**Зв'язки:**
- Один-до-одного з `"Users"` (Транзакція може мати одного покупця та продавця)
- Один-до-одного з `"Items"` (Транзакція може мати тільки один предмет)

### StickersOnWeapon
  
**Призначення:** Зберігає інформацію про наліпки на зброї.
| Стовпець | Тип | Обмеження | Опис |
|----------|-----|-----------|------|
| ID| SERIAL | PRIMARY KEY | Унікальний ID наліпки|
| ItemID | integer | NOT NULL   REFERENCES "Items" ("ID") ON DELETE CASCADE | ID зброї|
| StickerID | integer | NOT NULL   REFERENCES "Items" ("ID") ON DELETE CASCADE | ID предмета наліпки|
| PositionX| double precision | NOT NULL DEFAULT 0.0 | Позиція X наліпки|
| PositionY| double precision | NOT NULL DEFAULT 0.0 | Позиція Y наліпки|
| Rotation| double precision | NOT NULL DEFAULT 0.0 | Поворот наліпки|
| Wear| double precision | NOT NULL DEFAULT 0.0 | Поношеність наліпки|
| Scale| double precision | NOT NULL DEFAULT 0.0 | Розмір наліпки|

**Індекси**
- `idx_stickers_weapon ` на `"ItemID"`, для пошуку зброї з наліпками

**Зв'язки:**
- Один-до-одного з `"Items"` (Наліпка може бути на одному предметі)
- Один-до-одного з `"Items"` (Наліпка може бути одним предметом)

### ItemPreviews
  
**Призначення:** Містить зображення-preview предмета.

| Стовпець | Тип | Обмеження | Опис |
|----------|-----|-----------|------|
| ItemID | integer | PRIMARY KEY REFERENCES "Items" ("ID") ON DELETE CASCADE| ID предмету|
| Preview | bytea | - | Зображення|

**Зв'язки:**
- Один-до-одного з `"Items"` (Предмет може мати одне Preview)

### WeaponIDToWeapon
  
**Призначення:** Конвертує чисельні WeaponID у текстові Weapon.

| Стовпець | Тип | Обмеження | Опис |
|----------|-----|-----------|------|
| WeaponID| SERIAL | PRIMARY KEY | Чисельний WeaponID|
| Weapon| varchar(256) | NOT NULL | Текстовий Weapon|

**Зв'язки:**
- Один-до-багатьох з `"Items"` (Декілька предметів можуть мати ту саму зброю)

### ItemTypes
  
**Призначення:** Конвертує чисельні TypeID у текстові Description.

| Стовпець | Тип | Обмеження | Опис |
|----------|-----|-----------|------|
| TypeID| SERIAL | PRIMARY KEY | Чисельний TypeID|
| Description| varchar(256) | NOT NULL | Текстовий Description|

**Зв'язки:**
- Один-до-багатьох з `"Items"` (Декілька предметів можуть мати той самий тип)

### SpecialToCategory

**Призначення:** Конвертує чисельні SpecialID у текстові Category.

| Стовпець | Тип | Обмеження | Опис |
|----------|-----|-----------|------|
| SpecialID | SERIAL | PRIMARY KEY | Чисельний SpecialID |
| Category| varchar(256) | NOT NULL | Текстовий Category|

**Зв'язки:**
- Один-до-багатьох з `"Items"` (Декілька предметів можуть мати той самий спеціальний ефект)

### RestrictionType

**Призначення:** Конвертує чисельні Restriction ID у текстові RestDescription.

| Стовпець | Тип | Обмеження | Опис |
|----------|-----|-----------|------|
| ID | SERIAL | PRIMARY KEY | Чисельний Restriction ID |
| RestDescription | varchar(256) | NOT NULL | Текстовий RestDescription|

**Зв'язки:**
- Один-до-багатьох з `"Items"` (Декілька користувачів можуть мати те саме обмеження)

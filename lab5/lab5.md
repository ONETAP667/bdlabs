## 1. Функціональні залежності вихідної (ненормалізованої) схеми

Позначення: PK – первинний ключ; Кандидатні ключі у фігурних дужках.
    

### `WeaponIDToWeapon`

Атрибути:  
`WeaponID (PK), Weapon`
ФЗ (мінімальний набір):
`{WeaponID} → Weapon`

3НФ.

----------

### `ItemTypes`

Атрибути:  
`TypeID (PK), Description`
ФЗ:
`{TypeID} → Description`

3НФ.

----------

### `SpecialToCategory`
Атрибути:  
`SpecialID (PK), Category`
ФЗ:
`{SpecialID} → Category`
    
3НФ.

----------

### `Users`

Атрибути:  
`UserID (PK), Username, Balance, DateJoined, RestrictionType, RestrictedUntil, RestrictionReason`
ФЗ:
`{UserID} → Username, Balance, DateJoined, RestrictionType, RestrictedUntil, RestrictionReason`
    

3НФ.

----------

###  `Items`

(первісний дизайн)  
Атрибути:  
`ItemID (PK), OwnerID, Preview, Price, Type, Weapon, SkinID, Special, Float, Pattern, Nametag, Charm, CharmPattern, DateCreated`
ФЗ:
`{ItemID} → OwnerID, Preview, Price, Type, Weapon, SkinID, Special, Float, Pattern, Nametag, Charm, CharmPattern, DateCreated`
    

 3НФ.

----------

###  `Transactions`

Атрибути:  
`TransactionID (PK), SellerID, BuyerID, ItemID, Price, Date`
ФЗ:
 `{TransactionID} → SellerID, BuyerID, ItemID, Price, Date`
    
3НФ.

----------

###  `StickersOnWeapon`

Атрибути:

`ID (PK), ItemID, StickerID, Preview, PositionX, PositionY, Rotation, Wear, Scale`

На одній зброї (`ItemID`) кожен конкретний стікер (`StickerID`) може бути закріплений лише один раз.  
Кандидатний ключ: `{ItemID, StickerID}`.
    
Зображення прев’ю (`Preview`) фактично залежить лише від `ItemID`, а не від конкретного стікера.

Мінімальний набір ФЗ:

1.  `{ItemID, StickerID} → PositionX, PositionY, Rotation, Wear, Scale`  
    (пара «зброя–стікер» визначає позицію, знос тощо).
    
2.  `{ItemID} → Preview`  
    (будь-яка копія прев’ю для цієї зброї однакова).
    
3.  `{ID} → ItemID, StickerID, Preview, PositionX, PositionY, Rotation, Wear, Scale`  
    (штучний ключ).
    
З 1 та 2 випливає транзитивна залежність:

`{ItemID, StickerID} → ItemID → Preview`.

## 2. Найвища НФ вихідної схеми

Усі таблиці мають атомарні атрибути → **1НФ** виконується для всієї схеми.
    
Таблиці `WeaponIDToWeapon`, `ItemTypes`, `SpecialToCategory`, `Users`, `Items`, `Transactions` не мають складених ключів та транзитивних залежностей → **3НФ**.
    
Таблиця `StickersOnWeapon`:
    
 -  з точки зору природного ключа `{ItemID, StickerID}` має часткову залежність `{ItemID} → Preview` ⇒ **2НФ порушена**;
        
- та транзитивну залежність `{ItemID, StickerID} → ItemID → Preview` ⇒ **3НФ також порушена**.
        

Отже, вся схема як сукупність таблиць – не вище 1НФ, бо одна таблиця (`StickersOnWeapon`) не досягає 2НФ/3НФ.

## 3. Покрокова нормалізація

Нормалізуємо тільки `StickersOnWeapon`; інші таблиці лишаються без змін (вони вже у 3НФ).

**Таблиця S₀:**

`S₀(ID, ItemID, StickerID, Preview, PositionX, PositionY, Rotation, Wear, Scale)`

Ключі: Сурогатний ключ: `{ID}` – PK; Природний ключ: `{ItemID, StickerID}` – логічно унікальна пара.
    

ФЗ:

1.  `{ItemID, StickerID} → PositionX, PositionY, Rotation, Wear, Scale`
    
2.  `{ItemID} → Preview`
    
3.  `{ID} → ItemID, StickerID, Preview, PositionX, PositionY, Rotation, Wear, Scale`
    

**Проблеми:**

-   Часткова залежність: `Preview` залежить тільки від частини ключа (`ItemID`) → порушення 2НФ.
    
-   Транзитивна залежність: `{ItemID, StickerID} → ItemID → Preview` → порушення 3НФ.
    
-   Дублювання даних `Preview` для кожного стікера на одній і тій самій зброї.

Щоб прибрати часткову залежність `{ItemID} → Preview`, розкладаємо S₀ на дві таблиці:

1.  Таблиця прев’ю предмета:
    
    `P(ItemID, Preview)`
    
    -   Ключ: `{ItemID}`.
        
    -   ФЗ: `{ItemID} → Preview`.
        
2.  Таблиця `StickersOnWeapon` без прев’ю:
    
    `S₁(ID, ItemID, StickerID, PositionX, PositionY, Rotation, Wear, Scale)`
    
    -   Ключі: `{ID}` (PK) та альтернативний `{ItemID, StickerID}` (унікальність пари).
        
    -   ФЗ: `{ItemID, StickerID} → PositionX, PositionY, Rotation, Wear, Scale`.
        

Тепер у кожній таблиці всі неключові атрибути повністю залежать від усього ключа:

-   У P – від `ItemID`.
    
-   У S₁ – від `{ItemID, StickerID}` (або від `ID`).
    

**2НФ досягнута.**

Перевіряємо транзитивні залежності:

-   У `P(ItemID, Preview)` є тільки ФЗ `{ItemID} → Preview`. Немає атрибутів, які б залежали один від одного, крім ключа. 3НФ.
    
-   У `S₁` всі неключові атрибути (PositionX, PositionY, Rotation, Wear, Scale) залежать тільки від ключа `{ItemID, StickerID}` або від PK `ID`. Немає залежностей виду `Wear → PositionX` тощо. 3НФ.
    

Отже, після розкладання `StickersOnWeapon` на `ItemPreviews` (P) та новий `StickersOnWeapon` (S₁) **усі таблиці схеми перебувають у 3НФ**.

## 4. ALTER TABLE
`
CREATE TABLE "ItemPreviews"
(
    "ItemID"  integer PRIMARY KEY
        REFERENCES "Items" ("ItemID") ON DELETE CASCADE,
    "Preview" text NOT NULL
);`

`
ALTER TABLE "Items"
    DROP COLUMN "Preview";
`

`ALTER TABLE "StickersOnWeapon"
    DROP COLUMN "Preview";
`
`ALTER TABLE "StickersOnWeapon"
    ADD CONSTRAINT "FK_StickersOnWeapon_Sticker"
        FOREIGN KEY ("StickerID")
        REFERENCES "Items" ("ItemID");
`
`
ALTER TABLE "StickersOnWeapon"
    ADD CONSTRAINT "UQ_StickersOnWeapon_Item_Sticker"
        UNIQUE ("ItemID", "StickerID");`

**Фінальні таблиці у 3НФ  — у файлі normalized_tables**

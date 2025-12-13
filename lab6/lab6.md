## 4. Нова таблиця
Додаємо `ItemPreviews` до `schema.prisma`:
```
model ItemPreviews {
  ItemID Int   @id
  Preview Bytes?
 Items Items @relation(fields: [ItemID], references: [ItemID], onDelete: Cascade)
 }
 ```
Треба також додати відповідний зв'язок до `Items`: 
### До:
```
model Items {
  ItemID            Int                @id @default(autoincrement())
  OwnerID           Int
  Preview           String?
  Price             Int                @default(0)
  Type              Int?
  WeaponID          Int?
  SkinID            Int                @default(0)
  Special           Int
  Float             Float              @default(0.0)
  Pattern           Int                @default(0)
  Nametag           String?            @db.VarChar(256)
  Charm             Int?
  CharmPattern      Int?
  Users             Users              @relation(fields: [OwnerID], references: [UserID], onDelete: NoAction, onUpdate: NoAction)
  SpecialToCategory SpecialToCategory  @relation(fields: [Special], references: [SpecialID], onDelete: NoAction, onUpdate: NoAction)
  ItemTypes         ItemTypes?         @relation(fields: [Type], references: [TypeID], onDelete: NoAction, onUpdate: NoAction)
  WeaponIDToWeapon  WeaponIDToWeapon?  @relation(fields: [WeaponID], references: [WeaponID], onDelete: NoAction, onUpdate: NoAction)
  StickersOnWeapon  StickersOnWeapon[]
  Transactions      Transactions[]
}
```
### Після:
```
model Items {
  ItemID            Int                @id @default(autoincrement())
  OwnerID           Int
  Preview           String?
  Price             Int                @default(0)
  Type              Int?
  WeaponID          Int?
  SkinID            Int                @default(0)
  Special           Int
  Float             Float              @default(0.0)
  Pattern           Int                @default(0)
  Nametag           String?            @db.VarChar(256)
  Charm             Int?
  CharmPattern      Int?
  Users             Users              @relation(fields: [OwnerID], references: [UserID], onDelete: NoAction, onUpdate: NoAction)
  SpecialToCategory SpecialToCategory  @relation(fields: [Special], references: [SpecialID], onDelete: NoAction, onUpdate: NoAction)
  ItemTypes         ItemTypes?         @relation(fields: [Type], references: [TypeID], onDelete: NoAction, onUpdate: NoAction)
  WeaponIDToWeapon  WeaponIDToWeapon?  @relation(fields: [WeaponID], references: [WeaponID], onDelete: NoAction, onUpdate: NoAction)
  StickersOnWeapon  StickersOnWeapon[]
  Transactions      Transactions[]

  ItemPreview ItemPreviews?
}
```
Після цього — `npx prisma migrate dev --name add-itempreviews-table`
### Результат:
```
Loaded Prisma config from prisma.config.ts.
'clear' is not recognized as an internal or external command,
Prisma config detected, skipping environment variable loading.
Prisma schema loaded from prisma\schema.prisma
Datasource "db": PostgreSQL database "cs", schema "public" at "localhost:5432"

Applying migration `20251213122138_add_itempreviews_table`

The following migration(s) have been created and applied from new schema changes:

prisma\migrations/
  └─ 20251213122138_add_itempreviews_table/
    └─ migration.sql

Your database is now in sync with your schema.

✔ Generated Prisma Client (6.19.1) to .\generated\prisma in 77ms
```
## 5. Зміна існуючої таблиці
Додаємо `isActive` до `Users`:
### До:
```
model Users {
  UserID                                    Int            @id @default(autoincrement())
  Username                                  String         @db.VarChar(256)
  Balance                                   Int            @default(0)
  DateJoined                                DateTime       @default(now()) @db.Timestamptz(6)
  RestrictionType                           Int?
  RestrictedUntil                           DateTime?      @db.Timestamptz(6)
  RestrictionReason                         String?        @db.VarChar(256)
  Items                                     Items[]
  Transactions_Transactions_BuyerIDToUsers  Transactions[] @relation("Transactions_BuyerIDToUsers")
  Transactions_Transactions_SellerIDToUsers Transactions[] @relation("Transactions_SellerIDToUsers")
}
```
### Після:
```
model Users {
  UserID                                    Int            @id @default(autoincrement())
  Username                                  String         @db.VarChar(256)
  Balance                                   Int            @default(0)
  DateJoined                                DateTime       @default(now()) @db.Timestamptz(6)
  RestrictionType                           Int?
  RestrictedUntil                           DateTime?      @db.Timestamptz(6)
  RestrictionReason                         String?        @db.VarChar(256)
  isActive Boolean @default(true)  
  Items                                     Items[]
  Transactions_Transactions_BuyerIDToUsers  Transactions[] @relation("Transactions_BuyerIDToUsers")
  Transactions_Transactions_SellerIDToUsers Transactions[] @relation("Transactions_SellerIDToUsers")
}
```
Після цього — `npx prisma migrate dev --name add-users-isactive-field`
### Результат:
```
Loaded Prisma config from prisma.config.ts.

Prisma config detected, skipping environment variable loading.
Prisma schema loaded from prisma\schema.prisma
Datasource "db": PostgreSQL database "cs", schema "public" at "localhost:5432"

Applying migration `20251213124726_add_users_isactive_field`

The following migration(s) have been created and applied from new schema changes:

prisma\migrations/
  └─ 20251213124726_add_users_isactive_field/
    └─ migration.sql

Your database is now in sync with your schema.

✔ Generated Prisma Client (6.19.1) to .\generated\prisma in 78ms
```
## 6. Видалення стовпця
Видаляємо `RestrictionReason` із `Users`:
### До:
```
model Users {
  UserID                                    Int            @id @default(autoincrement())
  Username                                  String         @db.VarChar(256)
  Balance                                   Int            @default(0)
  DateJoined                                DateTime       @default(now()) @db.Timestamptz(6)
  RestrictionType                           Int?
  RestrictedUntil                           DateTime?      @db.Timestamptz(6)
  RestrictionReason                         String?        @db.VarChar(256)
  isActive Boolean @default(true)  
  Items                                     Items[]
  Transactions_Transactions_BuyerIDToUsers  Transactions[] @relation("Transactions_BuyerIDToUsers")
  Transactions_Transactions_SellerIDToUsers Transactions[] @relation("Transactions_SellerIDToUsers")
}
```
### Після:
```
model Users {
  UserID                                    Int            @id @default(autoincrement())
  Username                                  String         @db.VarChar(256)
  Balance                                   Int            @default(0)
  DateJoined                                DateTime       @default(now()) @db.Timestamptz(6)
  RestrictionType                           Int?
  RestrictedUntil                           DateTime?      @db.Timestamptz(6)
  isActive                                  Boolean        @default(true)
  Items                                     Items[]
  Transactions_Transactions_BuyerIDToUsers  Transactions[] @relation("Transactions_BuyerIDToUsers")
  Transactions_Transactions_SellerIDToUsers Transactions[] @relation("Transactions_SellerIDToUsers")
}
```
Після цього — `npx prisma migrate dev --name drop-users-restrictionreason`
### Результат:
```
Loaded Prisma config from prisma.config.ts.

Prisma config detected, skipping environment variable loading.
Prisma schema loaded from prisma\schema.prisma
Datasource "db": PostgreSQL database "cs", schema "public" at "localhost:5432"

Applying migration `20251213125348_drop_users_restrictionreason`

The following migration(s) have been created and applied from new schema changes:

prisma\migrations/
  └─ 20251213125348_drop_users_restrictionreason/
    └─ migration.sql

Your database is now in sync with your schema.

✔ Generated Prisma Client (6.19.1) to .\generated\prisma in 77ms
```

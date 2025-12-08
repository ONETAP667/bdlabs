DROP TABLE IF EXISTS "StickersOnWeapon" CASCADE;
DROP TABLE IF EXISTS "Transactions" CASCADE;
DROP TABLE IF EXISTS "ItemPreviews" CASCADE;
DROP TABLE IF EXISTS "Items" CASCADE;
DROP TABLE IF EXISTS "Users" CASCADE;
DROP TABLE IF EXISTS "WeaponIDToWeapon" CASCADE;
DROP TABLE IF EXISTS "ItemTypes" CASCADE;
DROP TABLE IF EXISTS "SpecialToCategory" CASCADE;


CREATE TABLE IF NOT EXISTS "WeaponIDToWeapon"
(
    "WeaponID"  SERIAL PRIMARY KEY,
    "Weapon"    varchar(256) NOT NULL
);

CREATE TABLE IF NOT EXISTS "ItemTypes"
(
    "TypeID"     SERIAL PRIMARY KEY,
    "Description" varchar(256)
);

CREATE TABLE IF NOT EXISTS "SpecialToCategory"
(
    "SpecialID"  SERIAL PRIMARY KEY,
    "Category"   varchar(256) NOT NULL
);


CREATE TABLE IF NOT EXISTS "Users"
(
    "UserID"            SERIAL PRIMARY KEY,
    "Username"          varchar(256) NOT NULL,
    "Balance"           integer NOT NULL DEFAULT 0,
    "DateJoined"        timestamptz NOT NULL DEFAULT now(),
    "RestrictionType"   integer,
    "RestrictedUntil"   timestamptz,
    "RestrictionReason" varchar(256)
);


CREATE TABLE IF NOT EXISTS "Items"
(
    "ItemID"       SERIAL PRIMARY KEY,
    "OwnerID"      integer NOT NULL
        REFERENCES "Users" ("UserID"),
    "Price"        integer NOT NULL DEFAULT 0,
    "Type"         integer
        REFERENCES "ItemTypes" ("TypeID"),
    "Weapon"       integer
        REFERENCES "WeaponIDToWeapon"("WeaponID"),
    "SkinID"       integer NOT NULL DEFAULT 0,
    "Special"      integer NOT NULL
        REFERENCES "SpecialToCategory"("SpecialID"),
    "Float"        double precision NOT NULL DEFAULT 0.0,
    "Pattern"      integer NOT NULL DEFAULT 0,
    "Nametag"      varchar(256),
    "Charm"        integer,
    "CharmPattern" integer,
    "DateCreated"  timestamptz NOT NULL DEFAULT now()
);


CREATE TABLE IF NOT EXISTS "ItemPreviews"
(
    "ItemID"  integer PRIMARY KEY
        REFERENCES "Items" ("ItemID") ON DELETE CASCADE,
    "Preview" text NOT NULL
);


CREATE TABLE IF NOT EXISTS "Transactions"
(
    "TransactionID" SERIAL PRIMARY KEY,
    "SellerID"      integer REFERENCES "Users" ("UserID"),
    "BuyerID"       integer REFERENCES "Users" ("UserID"),
    "ItemID"        integer REFERENCES "Items" ("ItemID"),
    "Price"         integer NOT NULL,
    "Date"          timestamptz NOT NULL
);


CREATE TABLE IF NOT EXISTS "StickersOnWeapon"
(
    "ID"        SERIAL PRIMARY KEY,
    "ItemID"    integer NOT NULL
        REFERENCES "Items" ("ItemID") ON DELETE CASCADE,
    "StickerID" integer NOT NULL
        REFERENCES "Items" ("ItemID") ON DELETE CASCADE,
    "PositionX" double precision NOT NULL,
    "PositionY" double precision NOT NULL,
    "Rotation"  double precision NOT NULL DEFAULT 0.0,
    "Wear"      double precision NOT NULL DEFAULT 0.0,
    "Scale"     double precision NOT NULL DEFAULT 1.0,
    CONSTRAINT "UQ_StickersOnWeapon_Item_Sticker"
        UNIQUE ("ItemID", "StickerID")
);

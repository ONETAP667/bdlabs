-- Table: WeaponIDToWeapon

-- DROP TABLE IF EXISTS "WeaponIDToWeapon";

CREATE TABLE IF NOT EXISTS "WeaponIDToWeapon"
(
    "WeaponID"  SERIAL PRIMARY KEY,
    "Weapon"  varchar(256) NOT NULL
)

TABLESPACE pg_default;

ALTER TABLE IF EXISTS "WeaponIDToWeapon"
    OWNER to postgres;


-- Table: ItemTypes

-- DROP TABLE IF EXISTS "ItemTypes";

CREATE TABLE IF NOT EXISTS "ItemTypes"
(
    "TypeID"  SERIAL PRIMARY KEY,
    "Description" varchar(256)
)

TABLESPACE pg_default;

ALTER TABLE IF EXISTS "ItemTypes"
    OWNER to postgres;


-- Table: SpecialToCategory

-- DROP TABLE IF EXISTS "SpecialToCategory";

CREATE TABLE IF NOT EXISTS "SpecialToCategory"
(
    "SpecialID"  SERIAL PRIMARY KEY,
    "Category" varchar(256) NOT NULL
)

TABLESPACE pg_default;

ALTER TABLE IF EXISTS "SpecialToCategory"
    OWNER to postgres;

-- Table: Users

-- DROP TABLE IF EXISTS "Users";

CREATE TABLE IF NOT EXISTS "Users"
(
    "UserID"  SERIAL PRIMARY KEY,
    "Username" varchar(256) NOT NULL,
    "Balance" integer NOT NULL DEFAULT 0,
    "DateJoined" timestamp with time zone NOT NULL DEFAULT now(),
    "RestrictionType" integer,
    "RestrictedUntil" timestamp with time zone,
    "RestrictionReason" varchar(256)
)

TABLESPACE pg_default;

ALTER TABLE IF EXISTS "Users"
    OWNER to postgres;

-- Table: Items

-- DROP TABLE IF EXISTS "Items";

CREATE TABLE IF NOT EXISTS "Items"
(
    "ItemID"  SERIAL PRIMARY KEY,
    "OwnerID" integer REFERENCES "Users"("UserID") NOT NULL,
    "Preview" text,
    "Price" integer NOT NULL DEFAULT 0,
    "Type" integer REFERENCES "ItemTypes" ("TypeID") ,
    "WeaponID" integer REFERENCES "WeaponIDToWeapon"("WeaponID"),
    "SkinID" integer NOT NULL DEFAULT 0,
    "Special" integer REFERENCES "SpecialToCategory"("SpecialID") NOT NULL,
    "Float" double precision NOT NULL DEFAULT 0.0,
    "Pattern" integer NOT NULL DEFAULT 0,
    "Nametag" varchar(256),
    "Charm" integer,
    "CharmPattern" integer
)

TABLESPACE pg_default;

ALTER TABLE IF EXISTS "Items"
    OWNER to postgres;
-- Table: Transactions

-- DROP TABLE IF EXISTS "Transactions";

CREATE TABLE IF NOT EXISTS "Transactions"
(
    "TransactionID"  SERIAL PRIMARY KEY,
    "SellerID" integer REFERENCES "Users" ("UserID"),
    "BuyerID" integer REFERENCES "Users" ("UserID"),
    "ItemID" integer REFERENCES "Items" ("ItemID"),
    "Price" integer NOT NULL,
    "Date" timestamp with time zone NOT NULL
)

TABLESPACE pg_default;

ALTER TABLE IF EXISTS "Transactions"
    OWNER to postgres;
-- Table: StickersOnWeapon

-- DROP TABLE IF EXISTS "StickersOnWeapon";

CREATE TABLE IF NOT EXISTS "StickersOnWeapon"
(
    "ID"  SERIAL PRIMARY KEY,
    "ItemID" integer REFERENCES "Items" ("ItemID"),
    "StickerID" integer NOT NULL,
    "Preview" text,
    "PositionX" double precision NOT NULL,
    "PositionY" double precision NOT NULL,
    "Rotation" double precision NOT NULL DEFAULT 0.0,
    "Wear" double precision NOT NULL DEFAULT 0.0,
    "Scale" double precision NOT NULL DEFAULT 1.0
)

TABLESPACE pg_default;

ALTER TABLE IF EXISTS "StickersOnWeapon"
    OWNER to postgres;


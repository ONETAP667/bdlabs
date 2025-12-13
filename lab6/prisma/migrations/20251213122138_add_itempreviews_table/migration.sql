-- CreateTable
CREATE TABLE "ItemTypes" (
    "TypeID" SERIAL NOT NULL,
    "Description" VARCHAR(256),

    CONSTRAINT "ItemTypes_pkey" PRIMARY KEY ("TypeID")
);

-- CreateTable
CREATE TABLE "Items" (
    "ItemID" SERIAL NOT NULL,
    "OwnerID" INTEGER NOT NULL,
    "Preview" TEXT,
    "Price" INTEGER NOT NULL DEFAULT 0,
    "Type" INTEGER,
    "WeaponID" INTEGER,
    "SkinID" INTEGER NOT NULL DEFAULT 0,
    "Special" INTEGER NOT NULL,
    "Float" DOUBLE PRECISION NOT NULL DEFAULT 0.0,
    "Pattern" INTEGER NOT NULL DEFAULT 0,
    "Nametag" VARCHAR(256),
    "Charm" INTEGER,
    "CharmPattern" INTEGER,

    CONSTRAINT "Items_pkey" PRIMARY KEY ("ItemID")
);

-- CreateTable
CREATE TABLE "SpecialToCategory" (
    "SpecialID" SERIAL NOT NULL,
    "Category" VARCHAR(256) NOT NULL,

    CONSTRAINT "SpecialToCategory_pkey" PRIMARY KEY ("SpecialID")
);

-- CreateTable
CREATE TABLE "StickersOnWeapon" (
    "ID" SERIAL NOT NULL,
    "ItemID" INTEGER,
    "StickerID" INTEGER NOT NULL,
    "Preview" TEXT,
    "PositionX" DOUBLE PRECISION NOT NULL,
    "PositionY" DOUBLE PRECISION NOT NULL,
    "Rotation" DOUBLE PRECISION NOT NULL DEFAULT 0.0,
    "Wear" DOUBLE PRECISION NOT NULL DEFAULT 0.0,
    "Scale" DOUBLE PRECISION NOT NULL DEFAULT 1.0,

    CONSTRAINT "StickersOnWeapon_pkey" PRIMARY KEY ("ID")
);

-- CreateTable
CREATE TABLE "Transactions" (
    "TransactionID" SERIAL NOT NULL,
    "SellerID" INTEGER,
    "BuyerID" INTEGER,
    "ItemID" INTEGER,
    "Price" INTEGER NOT NULL,
    "Date" TIMESTAMPTZ(6) NOT NULL,

    CONSTRAINT "Transactions_pkey" PRIMARY KEY ("TransactionID")
);

-- CreateTable
CREATE TABLE "Users" (
    "UserID" SERIAL NOT NULL,
    "Username" VARCHAR(256) NOT NULL,
    "Balance" INTEGER NOT NULL DEFAULT 0,
    "DateJoined" TIMESTAMPTZ(6) NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "RestrictionType" INTEGER,
    "RestrictedUntil" TIMESTAMPTZ(6),
    "RestrictionReason" VARCHAR(256),

    CONSTRAINT "Users_pkey" PRIMARY KEY ("UserID")
);

-- CreateTable
CREATE TABLE "WeaponIDToWeapon" (
    "WeaponID" SERIAL NOT NULL,
    "Weapon" VARCHAR(256) NOT NULL,

    CONSTRAINT "WeaponIDToWeapon_pkey" PRIMARY KEY ("WeaponID")
);

-- CreateTable
CREATE TABLE "ItemPreviews" (
    "ItemID" INTEGER NOT NULL,
    "Preview" BYTEA,

    CONSTRAINT "ItemPreviews_pkey" PRIMARY KEY ("ItemID")
);

-- AddForeignKey
ALTER TABLE "Items" ADD CONSTRAINT "Items_OwnerID_fkey" FOREIGN KEY ("OwnerID") REFERENCES "Users"("UserID") ON DELETE NO ACTION ON UPDATE NO ACTION;

-- AddForeignKey
ALTER TABLE "Items" ADD CONSTRAINT "Items_Special_fkey" FOREIGN KEY ("Special") REFERENCES "SpecialToCategory"("SpecialID") ON DELETE NO ACTION ON UPDATE NO ACTION;

-- AddForeignKey
ALTER TABLE "Items" ADD CONSTRAINT "Items_Type_fkey" FOREIGN KEY ("Type") REFERENCES "ItemTypes"("TypeID") ON DELETE NO ACTION ON UPDATE NO ACTION;

-- AddForeignKey
ALTER TABLE "Items" ADD CONSTRAINT "Items_WeaponID_fkey" FOREIGN KEY ("WeaponID") REFERENCES "WeaponIDToWeapon"("WeaponID") ON DELETE NO ACTION ON UPDATE NO ACTION;

-- AddForeignKey
ALTER TABLE "StickersOnWeapon" ADD CONSTRAINT "StickersOnWeapon_ItemID_fkey" FOREIGN KEY ("ItemID") REFERENCES "Items"("ItemID") ON DELETE NO ACTION ON UPDATE NO ACTION;

-- AddForeignKey
ALTER TABLE "Transactions" ADD CONSTRAINT "Transactions_BuyerID_fkey" FOREIGN KEY ("BuyerID") REFERENCES "Users"("UserID") ON DELETE NO ACTION ON UPDATE NO ACTION;

-- AddForeignKey
ALTER TABLE "Transactions" ADD CONSTRAINT "Transactions_ItemID_fkey" FOREIGN KEY ("ItemID") REFERENCES "Items"("ItemID") ON DELETE NO ACTION ON UPDATE NO ACTION;

-- AddForeignKey
ALTER TABLE "Transactions" ADD CONSTRAINT "Transactions_SellerID_fkey" FOREIGN KEY ("SellerID") REFERENCES "Users"("UserID") ON DELETE NO ACTION ON UPDATE NO ACTION;

-- AddForeignKey
ALTER TABLE "ItemPreviews" ADD CONSTRAINT "ItemPreviews_ItemID_fkey" FOREIGN KEY ("ItemID") REFERENCES "Items"("ItemID") ON DELETE CASCADE ON UPDATE CASCADE;

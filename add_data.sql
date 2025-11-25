DELETE FROM "StickersOnWeapon" ;
DELETE FROM "Items" ;
DELETE FROM "Users" ;
DELETE FROM "ItemTypes" ;
DELETE FROM "SpecialToCategory" ;
DELETE FROM "WeaponIDToWeapon"  ;

INSERT INTO "WeaponIDToWeapon"( "WeaponID", "Weapon") VALUES
	  ( 1, 'glock18'),
  	  ( 2, 'hkp2000'),
	  ( 3, 'usp_silencer'), 
	  ( 4, 'dualberettas'),
  	  ( 5, 'p250'),
	  ( 6, 'fiveseven'),
	  ( 7, 'tec9'),
  	  ( 8, 'cz75a'),
	  ( 9, 'deagle'),
	  ( 10, 'r8'),
  	  ( 11, 'mac10'),
	  ( 12, 'mp9'),
	  ( 13, 'mp7'),
  	  ( 14, 'mp5sd'),
	  ( 15, 'ump45'),
	  ( 16, 'p90'),
  	  ( 17, 'ppbizon'),
	  ( 18, 'nova'),
	  ( 19, 'xm1014'),
  	  ( 21, 'sawedoff'),
	  ( 22, 'mag7'),
	  ( 23, 'm249'),
  	  ( 24, 'negev'),
	  ( 25, 'galilar'),
	  ( 26, 'famas'),
  	  ( 27, 'ak47'),
	  ( 28, 'm4a1'),
	  ( 29, 'm4a1_silencer'),
  	  ( 30, 'ssg08'),
	  ( 31, 'sg556'),
	  ( 32, 'aug'),
  	  ( 33, 'awp'),
	  ( 34, 'g3sg1'),
	  ( 35, 'scar20'),
  	  ( 36, 'zeus27'),
	  ( 37, 'bayonet'),
	  ( 38, 'm9bayonet'),
  	  ( 39, 'karambit'),
	  ( 41, 'gut'),
	  ( 42, 'flip'),
  	  ( 43, 'huntsman'),
	  ( 44, 'butterfly'), 
	  ( 45, 'falchion'),
  	  ( 46, 'shadowdaggers'),
	  ( 47, 'bowie'),
	  ( 48, 'talon'),
  	  ( 49, 'ursus'),
	  ( 50, 'navaja'),
	  ( 51, 'stiletto'),
  	  ( 52, 'classic'),
	  ( 53, 'skeleton'),
	  ( 54, 'nomad'),
  	  ( 55, 'survival'),
	  ( 56, 'paracord'),
	  ( 57, 'kukri') ;

INSERT INTO "ItemTypes" (  "TypeID", "Description") VALUES
  ( 1, 'Weapon'),
  ( 2, 'Sticker'),
  ( 3, 'Container'),
  ( 4, 'Keychain') ;


INSERT INTO "SpecialToCategory"( "SpecialID", "Category") VALUES
	  ( 1, 'Normal'),
	  ( 2, 'Stattrak'),
	  ( 3, 'Souvenir'),
	  ( 4, 'Highlight') ;

INSERT INTO "Users" ( "UserID", "Username", "Balance") VALUES
  ( 1, 'User 1', 10000),
  ( 2, 'User 2', 20000),
  ( 3, 'User 3', 1000) ;

INSERT INTO "Items" ( "ItemID", "OwnerID", "Price", "Type", "WeaponID", "SkinID", "Special", "Float", "Pattern", "Nametag", "Charm", "CharmPattern") VALUES
  ( 1, 1, 100, 1, 3, 13, 1, 0.132468781, 841, 'Just a little pistol', 0, 0 ),
  ( 2, 1, 350, 1, 2, 81, 1, 0.884108217, 452, '', 0, 0 ), 
  ( 3, 1, 50, 2, 1, 14, 1, 0.0, 0,'', 0, 0 ) ,
  ( 4, 2, 1000, 1, 26, 29,  2, 0.00139843, 173, 'HEADSHOT MACHINE', 3, 18972 ),
  ( 5, 2, 500, 2, 1, 4,  1, 0.0, 0, '', 0, 0 ),
  ( 6, 2, 250, 4, 3, 13, 1, 0.0, 53129, '', 0, 0 ),
  ( 7, 2, 100, 3, 1, 9, 1, 0.0, 0, '', 0, 0 ),
  ( 8, 3, 300, 1, 3, 10, 3, 0.31298923, 189,  '',0, 0 ) ,
  ( 9, 3, 400, 2, 1, 3, 1, 0.0, 0, '', 0, 0 );


INSERT INTO "StickersOnWeapon"(  "ID", "ItemID", "StickerID", "PositionX", "PositionY", "Rotation", "Wear", "Scale") VALUES
  ( 1, 1, 18, 0.15, 0.25, 0.1, 0.25, 1.0),
  ( 2, 1, 23, 0.5, 0.65, 0.0, 0.1, 1.0) ,
  ( 3, 4, 11, 0.2, 0.4, 0.0, 0.0, 1.0) ,
  ( 4, 4, 11, 0.4, 0.4, 0.0, 0.0, 1.0) ,
  ( 5, 4, 11, 0.6, 0.4, 0.0, 0.0, 1.0) ,
  ( 6, 4, 11, 0.8, 0.4, 0.0, 0.0, 1.0) ;

INSERT INTO "Transactions" ("TransactionID", "SellerID", "BuyerID", "ItemID", "Price", "Date") VALUES 
  (1, 2, 1, 3, 100, NOW()) ;
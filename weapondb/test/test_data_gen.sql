INSERT INTO "Users"("ID","Username","Balance","DateJoined")
SELECT
    gs.id,
    'User_' || gs.id AS Username,
    (floor(random()*9000)+1000)::int AS Balance,                           -- 1000..10000
    now() - (interval '1 day' * floor(random()*730))                      -- äî 2 ëåò íàçàä
FROM generate_series(2,21) AS gs(id);  -- ãåíåðèðóåì ïîëüçîâàòåëåé ñ ID 2..21

------------------------------------------------------------------------------------------
INSERT INTO "Items"
("OwnerID", "Price", "Type", "Weapon", "Special", "Nametag", "DateCreated")
SELECT
    (floor(random()*20)+1)::int AS OwnerID,                         -- ïîëüçîâàòåëü 1..21
    (floor(random()*4900)+100)::int AS Price,                       -- 100..5000
    -- Ðàñïðåäåëåíèå Type ïî âåðîÿòíîñòè
    CASE
        WHEN rnd < 0.25 THEN 1       -- 25% Weapon
        WHEN rnd < 0.85 THEN 2       -- +60% Sticker = 85% ñóììàðíî
        WHEN rnd < 0.95 THEN 3       -- +10% Container
        ELSE 4                       -- +5% Keychain
    END AS Type,

    -- Weapon/Special òîëüêî åñëè Type=1
    CASE WHEN rnd < 0.25 THEN (floor(random()*57)+1)::int ELSE NULL END AS Weapon,
    CASE WHEN rnd < 0.25 THEN (floor(random()*4)+1)::int  ELSE NULL END AS Special,

    'Item_' || gs AS Nametag,

    -- Ñëó÷àéíàÿ äàòà çà ïîñëåäíèå 2 ãîäà
    now() - (interval '1 day' * floor(random()*730)) AS DateCreated

FROM generate_series(1,100) AS gs
CROSS JOIN LATERAL (SELECT random() AS rnd) AS r;

-------------------------------------------------------------------------------------------------
DROP TABLE IF EXISTS tmp_random_weapons;

CREATE TEMP TABLE tmp_random_weapons AS
SELECT
    "WeaponID",
    "Weapon",
    ROW_NUMBER() OVER (ORDER BY random()) AS rn
FROM "WeaponIDToWeapon";
INSERT INTO "Items"
("ID","OwnerID","Price","Type","Weapon","Special","Nametag","DateCreated")
SELECT
    gs AS ID,
    (floor(random()*20)+1)::int AS OwnerID,
    (floor(random()*200)+1)::int AS Price,
    1 AS Type,

    w."WeaponID" AS Weapon,
    (floor(random()*4)+1)::int AS Special,
    w."Weapon" || '_#' || gs AS Nametag,

    now() - (interval '1 day' * floor(random()*730)) AS DateCreated

FROM generate_series(1,20) AS gs

JOIN tmp_random_weapons w
    ON w.rn = ((gs - 1) % (SELECT COUNT(*) FROM tmp_random_weapons)) + 1;

-----------------------------------------------------------------------------------
DROP TABLE IF EXISTS tmp_sticker_names;

CREATE TEMP TABLE tmp_sticker_names AS
SELECT
    base_name,
    ROW_NUMBER() OVER (ORDER BY random()) AS rn
FROM (
    SELECT unnest(ARRAY[
        -- Team Stickers
        'Navi', 'FaZe', 'G2', 'Heroic', 'Liquid', 'Vitality', 'Astralis',

        -- Event Stickers
        'PGL_2024', 'Katto_2023', 'Rio_2022', 'Blast_2024', 'DreamHack',

        -- Player Autographs
        's1mple_sig', 'NiKo_sig', 'ZywOo_sig', 'device_sig', 'm0NESY_sig',

        -- Art / Graffiti
        'Flame', 'Dragon', 'Skull', 'PixelCat', 'WingedSkull', 'Toxic', 'GoldStar'
    ]) AS base_name
) q;

INSERT INTO "Items"
("ID","OwnerID","Price","Type","Nametag","DateCreated")
SELECT
    gs AS ID,
    (floor(random()*20)+1)::int     AS OwnerID,      -- ïîëüçîâàòåëè 1..21
    (floor(random()*50)+1)::int     AS Price,        -- 1..50
    2                                AS Type,        -- Sticker
    t.base_name || '_#' || gs       AS Nametag,
    now() - (interval '1 day' * floor(random()*730)) AS DateCreated
FROM generate_series(101,120) AS gs
JOIN tmp_sticker_names t
    ON t.rn = ((gs - 1) % (SELECT COUNT(*) FROM tmp_sticker_names)) + 1;
-----------------------------------------------------------------------------------

DROP TABLE IF EXISTS tmp_container_names;

CREATE TEMP TABLE tmp_container_names AS
SELECT
    base_name,
    ROW_NUMBER() OVER (ORDER BY random()) AS rn
FROM (
    SELECT unnest(ARRAY[
        -- Cases
        'BravoCase', 'PhoenixCase', 'WinterCase', 'SpectrumCase', 'HuntsmanCase',
        'FalchionCase', 'GloveCase', 'PrismaCase', 'RevolverCase', 'DreamHackCase',

        -- Collections / Boxes
        'DustCollectionBox', 'LakeCollectionBox', 'TrainCollectionBox',

        -- Capsules
        'StickerCapsule', 'AutographCapsule', 'LegendsCapsule', 'ChallengersCapsule',

        -- Souvenir packages
        'SouvenirDust2', 'SouvenirMirage', 'SouvenirInferno', 'SouvenirNuke',

        -- Misc
        'WeaponCrate', 'LootCrate', 'MilitaryBox', 'VintageCrate'
    ]) AS base_name
) q;

INSERT INTO "Items"
("ID","OwnerID","Price","Type","Nametag","DateCreated")
SELECT
    gs AS ID,
    (floor(random()*20)+1)::int AS OwnerID,                 -- UserID 1..21
    (floor(random()*250)+50)::int AS Price,                 -- 50..300
    3 AS Type,                                              -- Container
    t.base_name || '_#' || gs AS Nametag,
    now() - (interval '1 day' * floor(random()*730))        -- < 2 ëåò íàçàä
FROM generate_series(201,225) AS gs
JOIN tmp_container_names t
    ON t.rn = ((gs - 1) % (SELECT COUNT(*) FROM tmp_container_names)) + 1;

-----------------------------------------------------------------------------------
DROP TABLE IF EXISTS tmp_keychain_names;

CREATE TEMP TABLE tmp_keychain_names AS
SELECT
    base_name,
    ROW_NUMBER() OVER (ORDER BY random()) AS rn
FROM (
    SELECT unnest(ARRAY[
        -- Metallic / Military
        'SteelTag', 'DogTag', 'IronPlate', 'CombatHook', 'TacticalBadge',

        -- Animal / Skull
        'DragonCharm', 'WolfCharm', 'SkullCharm', 'SerpentCharm',

        -- Glow / Holo / Neon
        'HoloStar', 'NeonCube', 'PulseCharm', 'LaserKey',

        -- Cute / Fun
        'PixelHeart', 'MiniBot', 'ToyDuck', 'SmileyCharm', 'LuckyCoin',

        -- Weapon-based
        'MiniKnife', 'MicroAK', 'MicroAWP', 'BulletCharm'
    ]) AS base_name
) q;

INSERT INTO "Items"
("ID","OwnerID","Price","Type","Nametag","DateCreated")
SELECT
    gs AS ID,
    (floor(random()*20)+1)::int AS OwnerID,                -- Users 1..21
    (floor(random()*120)+30)::int AS Price,                -- 30..150
    4 AS Type,                                             -- Keychain
    t.base_name || '_#' || gs AS Nametag,
    now() - (interval '1 day' * floor(random()*730))       -- < 2 ëåò íàçàä
FROM generate_series(401,440) AS gs
JOIN tmp_keychain_names t
    ON t.rn = ((gs - 1) % (SELECT COUNT(*) FROM tmp_keychain_names)) + 1;
-----------------------------------------------------------------------------------
-- StickersOnWeapon
WITH weapons AS (
    SELECT "ID" AS weapon_id
    FROM "Items"
    WHERE "Type" = 1
),
stickers AS (
    SELECT "ID" AS sticker_id
    FROM "Items"
    WHERE "Type" = 2
      AND "ID" BETWEEN 101 AND 140
),
weapon_sticker_map AS (
    SELECT
        w.weapon_id,
        (floor(random()*3)+1)::int AS sticker_count,   -- 1..3
        (
            SELECT array_agg(s.sticker_id ORDER BY random())
            FROM stickers s
        ) AS shuffled_stickers
    FROM weapons w
),
expanded AS (
    SELECT
        weapon_id,
        shuffled_stickers[i] AS sticker_id
    FROM weapon_sticker_map,
         generate_subscripts(shuffled_stickers, 1) AS i
    WHERE i <= sticker_count
)
INSERT INTO "StickersOnWeapon"
("ItemID", "StickerID", "PositionX", "PositionY", "Rotation", "Wear", "Scale")
SELECT
    e.weapon_id AS ItemID,
    e.sticker_id AS StickerID,
    random() AS PositionX,
    random() AS PositionY,
    random() * 360.0 AS Rotation,
    random() * 0.5 AS Wear,
    0.75 + random() * 0.5 AS Scale
FROM expanded e;
-----------------------------------------------------------------------------------
INSERT INTO "StickersOnWeapon"
("ItemID", "StickerID", "PositionX", "PositionY", "Rotation", "Wear", "Scale")
SELECT
    w.weapon_id AS ItemID,
    c.container_id AS StickerID,
    random() AS PositionX,
    random() AS PositionY,
    random() * 360 AS Rotation,
    random() * 0.5 AS Wear,
    0.75 + random() * 0.5 AS Scale
FROM (
    SELECT "ID" AS weapon_id FROM "Items" WHERE "Type" = 1 ORDER BY "ID"
) w
JOIN (
    SELECT "ID" AS container_id FROM "Items" WHERE "Type" = 3 ORDER BY "ID"
) c
    ON c.container_id =
       ((w.weapon_id - 1) % (SELECT COUNT(*) FROM "Items" WHERE "Type" = 3)) +
       (SELECT MIN("ID") FROM "Items" WHERE "Type" = 3);
-----------------------------------------------------------------------------------
INSERT INTO "StickersOnWeapon"
("ItemID", "StickerID", "PositionX", "PositionY", "Rotation", "Wear", "Scale")
SELECT
    w.weapon_id AS ItemID,
    k.keychain_id AS StickerID,
    random() AS PositionX,
    random() AS PositionY,
    random() * 360 AS Rotation,
    random() * 0.5 AS Wear,
    0.75 + random() * 0.5 AS Scale
FROM (
    SELECT "ID" AS weapon_id FROM "Items" WHERE "Type" = 1 ORDER BY "ID"
) w
JOIN (
    SELECT "ID" AS keychain_id FROM "Items" WHERE "Type" = 4 ORDER BY "ID"
) k
    ON k.keychain_id =
       ((w.weapon_id - 1) % (SELECT COUNT(*) FROM "Items" WHERE "Type" = 4)) +
       (SELECT MIN("ID") FROM "Items" WHERE "Type" = 4);

----------------------------------------------------------------------------------------
--Transactions
DO $$
DECLARE
    item_rec    RECORD;
    seller_id   int;
    buyer_id    int;
    buyer_bal   int;
    required     int;
    price        int;
    tx_date      timestamptz;
    tx_count     int;
BEGIN
    -- Äëÿ êàæäîãî ïðåäìåòà ãåíåðèðóåì íåñêîëüêî ïðîäàæ
    FOR item_rec IN
        SELECT "ID" AS item_id
        FROM "Items"
        ORDER BY "ID"
    LOOP
        -- Êîë-âî òðàíçàêöèé: 1..5
        tx_count := (floor(random()*5)+1)::int;

        FOR i IN 1..tx_count LOOP

            -- Óçíà¸ì òåêóùåãî âëàäåëüöà
            SELECT "OwnerID"
            INTO seller_id
            FROM "Items"
            WHERE "ID" = item_rec.item_id;

            -- Âûáèðàåì ïîêóïàòåëÿ: íå ïðîäàâåö è íå Game Owner
            LOOP
                buyer_id := (floor(random()*20)+1)::int;
                EXIT WHEN buyer_id <> seller_id AND buyer_id <> 1;
            END LOOP;

            -- Ñëó÷àéíàÿ öåíà (íàïðèìåð, 50..500)
            price := (floor(random()*450)+50)::int;

            -- Óçíà¸ì áàëàíñ ïîêóïàòåëÿ
            SELECT "Balance"
            INTO buyer_bal
            FROM "Users"
            WHERE "ID" = buyer_id;

            -- Åñëè äåíåã íå õâàòàåò  ïîïîëíÿåì áàëàíñ
            IF buyer_bal < price THEN
                required := price - buyer_bal + 10;  -- +10 íà çàïàñ
                UPDATE "Users"
                SET "Balance" = "Balance" + required
                WHERE "ID" = buyer_id;
            END IF;

            -- Ñëó÷àéíàÿ äàòà â ïðåäåëàõ äâóõ ëåò
            tx_date := now() - (interval '1 day' * floor(random()*730));

            -- Ñîçäà¸ì òðàíçàêöèþ
            INSERT INTO "Transactions"
            ("SellerID", "BuyerID", "ItemID", "Price", "Date")
            VALUES
            (seller_id, buyer_id, item_rec.item_id, price, tx_date);

            -- Òðèããåð ñàì ñìåíèò âëàäåëüöà è ïåðåâåä¸ò äåíüãè
        END LOOP;

    END LOOP;
END $$;

--Canceled transactions

DO $$
DECLARE
    tx RECORD;
    cnt int;
BEGIN
    -- Êîëè÷åñòâî îòìåí: 515
    cnt := (floor(random()*11)+5)::int;

    FOR tx IN
        SELECT *
        FROM "Transactions"
        WHERE "Canceled" = false
        ORDER BY random()
        LIMIT cnt
    LOOP
        -- Ïðîâåðèì, ÷òî ïðåäìåò äî ñèõ ïîð ó ïîêóïàòåëÿ (èíà÷å îòìåíà íåâîçìîæíà)
        IF (SELECT "OwnerID" FROM "Items" WHERE "ID" = tx."ItemID") = tx."BuyerID" THEN

            -- Ñòàâèò Canceled = true è âûçûâàåò òðèããåð
            UPDATE "Transactions"
            SET "Canceled" = true
            WHERE "TransactionID" = tx."TransactionID";

        END IF;
    END LOOP;

END $$;



---- èêîíêè

INSERT INTO suppliers (id, name, company, phone, email, address, country, notes) VALUES
(1, 'Karim Bennani', 'Casablanca Diamonds SARL', '+212 522 123456', 'contact@casadiamonds.ma', '142 Boulevard d''Anfa', 'Morocco', 'Primary local certified supplier'),
(2, 'David & Sons Diamond Trading', 'Antwerp Gem Trading Co.', '+32 3 234 5678', 'orders@antwerpgem.be', 'Hoveniersstraat 32', 'Belgium', 'GIA certified natural diamonds'),
(3, 'Atlas Gemological Imports', 'Atlas Gems Marrakech', '+212 524 987654', 'info@atlasgems.ma', '45 Rue de la Liberte, Gueliz', 'Morocco', 'High carat fancy shapes');

INSERT INTO diamonds (
    id, reference, sku, barcode, name, description, shape, carat_weight, color, clarity, cut, polish, symmetry, fluorescence, fluorescence_color,
    table_percentage, depth_percentage, length_mm, width_mm, height_mm, girdle, culet,
    certificate_number, certificate_lab, certificate_date, certificate_url, certificate_notes,
    purchase_price_cents, selling_price_cents, discount_price_cents, min_selling_price_cents,
    status, location, location_details, supplier_id, is_favorite, archived
) VALUES
(
    1, 'DMD-00101', 'SKU-RND-101', '611100010101', 'Round Brilliant Solitaire', 'Exceptional triple excellent round brilliant diamond with brilliant fire.',
    'Round', 1.05, 'D', 'VVS1', 'Excellent', 'Excellent', 'Excellent', 'None', '',
    57.0, 61.5, 6.52, 6.55, 4.02, 'Medium', 'None',
    'GIA-218491024', 'GIA', '2025-11-15', '', 'Laser inscribed GIA 218491024',
    4800000, 6500000, 6200000, 5800000,
    'Available', 'Main Vault', 'Tray A - Slot 1', 2, 1, 0
),
(
    2, 'DMD-00102', 'SKU-OVAL-102', '611100010102', 'Oval Elegance Diamond', 'Stunning elongated oval cut with high clarity and minimal bowtie effect.',
    'Oval', 1.52, 'F', 'VS1', 'Very Good', 'Excellent', 'Very Good', 'Faint', 'Blue',
    59.0, 63.2, 9.15, 6.42, 4.05, 'Slightly Thick', 'None',
    'IGI-520194821', 'IGI', '2025-12-02', '', 'Certificate with digital verification',
    6200000, 8400000, 8000000, 7500000,
    'Available', 'Display Case 1', 'Top Shelf / Ring Stand B', 1, 1, 0
),
(
    3, 'DMD-00103', 'SKU-PRIN-103', '611100010103', 'Princess Cut Royale', 'Classic square modified brilliant with sharp corners and intense brilliance.',
    'Princess', 0.95, 'G', 'VS2', 'Excellent', 'Excellent', 'Very Good', 'None', '',
    68.0, 72.1, 5.40, 5.38, 3.88, 'Medium', 'None',
    'GIA-639102488', 'GIA', '2026-01-10', '', 'Includes lab report dossier',
    2800000, 3900000, 3750000, 3400000,
    'Reserved', 'Safe Deposit', 'Box #4', 1, 0, 0
),
(
    4, 'DMD-00104', 'SKU-EMR-104', '611100010104', 'Emerald Cut Vintage', 'Sophisticated step cut diamond with mesmerizing hall-of-mirrors effect.',
    'Emerald', 2.10, 'E', 'VVS2', 'Very Good', 'Excellent', 'Excellent', 'None', '',
    64.0, 66.8, 8.60, 6.10, 4.07, 'Medium', 'None',
    'HRD-22004819', 'HRD', '2025-10-20', '', 'Antwerp certified',
    11500000, 15800000, 15000000, 14000000,
    'Available', 'Main Vault', 'Tray B - Slot 4', 2, 1, 0
),
(
    5, 'DMD-00105', 'SKU-CUSH-105', '611100010105', 'Cushion Modified Brilliant', 'Romantic pillow-shaped diamond with soft rounded corners and deep fire.',
    'Cushion', 1.25, 'H', 'SI1', 'Good', 'Very Good', 'Good', 'Medium', 'Blue',
    61.0, 65.4, 6.70, 6.35, 4.15, 'Thick', 'Small',
    'IGI-489102377', 'IGI', '2026-02-05', '', '',
    3400000, 4700000, 4500000, 4200000,
    'Sold', 'Store Archive', 'Delivered to Customer Order #892', 3, 0, 0
),
(
    6, 'DMD-00106', 'SKU-PEAR-106', '611100010106', 'Pear Shaped Teardrop', 'Graceful pear cut with balanced proportions and sparkling teardrop tip.',
    'Pear', 0.85, 'G', 'VS1', 'Very Good', 'Excellent', 'Very Good', 'None', '',
    58.5, 62.8, 7.85, 5.12, 3.21, 'Medium', 'None',
    'GIA-719382104', 'GIA', '2026-01-22', '', '',
    2400000, 3350000, 3200000, 2900000,
    'Available', 'Display Case 2', 'Tray C - Slot 2', 1, 0, 0
),
(
    7, 'DMD-00107', 'SKU-RAD-107', '611100010107', 'Radiant Cut Sparkler', 'Vibrant hybrid combining emerald shape elegance with brilliant cut facet sparkle.',
    'Radiant', 1.70, 'D', 'VS2', 'Excellent', 'Excellent', 'Excellent', 'None', '',
    66.0, 69.5, 7.45, 6.30, 4.38, 'Medium to Thick', 'None',
    'GIA-839201948', 'GIA', '2026-02-14', '', '',
    7900000, 10800000, 10300000, 9600000,
    'Available', 'Main Vault', 'Tray A - Slot 5', 3, 1, 0
),
(
    8, 'DMD-00108', 'SKU-MARQ-108', '611100010108', 'Marquise Navette Diamond', 'Dramatic football-shaped diamond maximizing carat spread and brilliance.',
    'Marquise', 1.12, 'I', 'SI1', 'Good', 'Good', 'Very Good', 'Strong', 'Blue',
    60.0, 63.0, 10.40, 5.20, 3.28, 'Extremely Thick', 'None',
    'IGI-918237190', 'IGI', '2025-09-18', '', '',
    2600000, 3600000, 3450000, 3100000,
    'Available', 'Display Case 1', 'Tray D - Slot 1', 1, 0, 0
);

INSERT INTO app_settings (key, value) VALUES
('store_name', 'Maison du Diamant'),
('store_address', 'Boulevard Al Massira Al Khadra, Casablanca, Maroc'),
('store_phone', '+212 522 998877'),
('store_email', 'contact@maison-diamant.ma'),
('currency_code', 'MAD'),
('currency_symbol', 'MAD'),
('theme_mode', 'Dark'),
('auto_backup_interval', 'daily'),
('last_backup_date', '');

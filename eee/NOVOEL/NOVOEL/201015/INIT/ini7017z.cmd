
-- Init 7017 --
MOD1 02 9600 07 40

COM1
-- Adress I7017Z  AA=02
-- Read name
$02M
-- Set TT=07,9600 baud, FF=40
%0202070640
-- enable all inputs
$02503FF
-- diff.inputs
@02S0
-- channel 0 - 4...20 mA  (07)
$027C0R07
-- channel 6 - 4...20 mA  (07)
$027C6R07
-- channel 7 - 4...20 mA  (07)
$027C7R07
-- read channel modes
$028C0
$028C1
$028C2
$028C3
$028C4
$028C5
$028C6
$028C7
$028C8
$028C9


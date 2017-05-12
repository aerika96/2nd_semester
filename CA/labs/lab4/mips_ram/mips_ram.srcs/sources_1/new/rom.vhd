library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity rom is
    Port(
        address: in std_logic_vector(3 downto 0);
        output : out std_logic_vector(15 downto 0)
    );
end entity;

architecture Behav of rom is
type mem is array (0 to 14) of std_logic_vector(15 downto 0);
signal rom_mem : mem:=(
b"000_001_010_011_0_000",
b"000_001_010_011_0_001",
b"000_001_010_011_1_010",
b"000_001_010_011_1_011",
b"000_001_010_011_0_100",
b"000_001_010_011_0_101",
b"000_001_010_011_0_110",
b"000_001_010_011_1_111",
b"001_001_010_0000001",
b"010_001_010_0000010",
b"011_001_010_0000011",
b"100_001_010_0000100",
b"101_001_010_0000101",
b"110_001_010_0000110",
b"111_000000000000111",
others => b"1111111111111111"
);
begin

output<=rom_mem(conv_integer(address));
end  architecture ;  
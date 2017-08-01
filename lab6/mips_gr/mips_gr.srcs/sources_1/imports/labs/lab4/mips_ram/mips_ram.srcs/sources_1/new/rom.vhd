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
type mem is array (0 to 24) of std_logic_vector(15 downto 0);
signal rom_mem : mem:=(
b"000_001_010_011_0_000",-- r-type add
b"000_001_010_011_0_001",-- r-type sub
b"000_001_010_011_1_010",-- r-type sll
b"000_001_010_011_1_011",-- r-type srr
b"000_001_010_011_0_100",-- r-type and
b"000_001_010_011_0_101",-- r-type or
b"000_001_010_011_0_110",-- r-type xor
b"000_001_010_011_1_111",-- r-type sar
b"001_001_010_0000001",-- i-type addi
b"010_001_010_0000010",-- i-type lw
b"000_000_000_000_0_000", -- nop
b"000_000_000_000_0_000", -- nop
b"011_001_010_0000010",-- sw
b"100_001_010_0000100",-- beq
b"000_000_000_000_0_000", -- nop
b"000_000_000_000_0_000", -- nop
b"000_000_000_000_0_000", -- nop
b"101_001_010_0000101",-- andi
b"110_001_000_0000010",-- bgez
b"000_000_000_000_0_000", -- nop
b"000_000_000_000_0_000", -- nop
b"000_000_000_000_0_000", -- nop
b"111_0000000000111",--jmp
b"000_000_000_000_0_000", -- nop
others => b"1111111111111111"
);
begin

output<=rom_mem(conv_integer(address));
end  architecture ;  
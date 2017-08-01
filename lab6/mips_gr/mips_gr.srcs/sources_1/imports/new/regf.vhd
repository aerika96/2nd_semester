----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/17/2017 07:06:40 AM
-- Design Name: 
-- Module Name: regf - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity regf is
  Port ( 
    clk:in std_logic;
    regwr: in std_logic;
    ra1: in std_logic_vector(2 downto 0);
    ra2: in std_logic_vector(2 downto 0);
    wa : in std_logic_vector(2 downto 0);
    wd : in std_logic_vector (15 downto 0);
    rd1 : out std_logic_vector (15 downto 0);
    rd2 : out std_logic_vector (15 downto 0)
  );
end regf;

architecture Behavioral of regf is
type mem is array  (0 to 16 )of std_logic_vector(15 downto 0);
signal memory : mem := (
    x"0000",
    x"0002",
    x"0003",
    x"0004",
    x"0005",
    x"0006",
    x"000A",
    x"000B" ,
    others => x"ABCD"   
);
begin

process(clk,regwr,memory)
begin
if(rising_edge(clk))then
if(regwr='1')then
memory(conv_integer(wa))<=wd;
end if;
end if;
end process;
rd1 <= memory(conv_integer(ra1));
rd2 <= memory(conv_integer(ra2));
end Behavioral;

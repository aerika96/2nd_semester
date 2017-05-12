----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04/20/2017 06:29:43 PM
-- Design Name: 
-- Module Name: data_memory - Behavioral
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

entity data_memory is
  Port ( 
    clk:in std_logic;
    address: in std_logic_vector(15 downto 0);
    re:in std_logic;
    we: in std_logic;
    write_data: in std_logic_vector(15 downto 0);
    address_content:out std_logic_vector(15 downto 0);
    output:out std_logic_vector(15 downto 0)
  );
end data_memory;

architecture Behavioral of data_memory is
type mem is array (0 to 50) of std_logic_vector(15 downto 0);
signal rom_mem : mem:=(
  x"1234",
  x"2345",
  x"3456",
  x"4567",
  x"5678",
  x"6789",
  x"789A",
  x"89AB",
  x"9ABC",
  x"ABCD",
  x"BCDE",
  x"CDEF",
  others => x"FFFF"

);
begin

address_content<=rom_mem(conv_integer(address));
process(clk,we, re)
begin
if(rising_edge(clk)) then
    if(we='1') then
    rom_mem(conv_integer(address))<=write_data;
    elsif(re='1')then
    output<=rom_mem(conv_integer(address));
    end if;
end if;
end process;
end Behavioral;

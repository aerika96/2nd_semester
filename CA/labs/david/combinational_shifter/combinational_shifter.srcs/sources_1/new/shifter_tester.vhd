----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/10/2017 06:11:55 PM
-- Design Name: 
-- Module Name: shifter_tester - Behavioral
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

entity shifter_tester is
Port ( sw : in std_logic_vector(15 downto 0);
         btn : in std_logic_vector(4 downto 0);
         led : out std_logic_vector(15 downto 0);
         an : out std_logic_vector(3 downto 0);
         cat : out std_logic_vector(6 downto 0);
         clk : in std_logic
         );
end shifter_tester;

architecture Behavioral of shifter_tester is

component combinational_shifter is
    Port (
           A : in STD_LOGIC_VECTOR (4 downto 0);
           S : in STD_LOGIC_VECTOR (1 downto 0);
           dir : in STD_LOGIC;
           R : out STD_LOGIC_VECTOR (4 downto 0));
end component;

begin
    shifter : combinational_shifter port map (A=>sw(4 downto 0), S=>sw(6 downto 5), dir=>sw(7), R=>led(4 downto 0));

end Behavioral;

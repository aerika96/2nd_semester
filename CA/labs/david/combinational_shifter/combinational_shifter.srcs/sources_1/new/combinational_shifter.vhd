----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/10/2017 05:46:17 PM
-- Design Name: 
-- Module Name: combinational_shifter - Behavioral
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

entity combinational_shifter is
    Port (
           A : in STD_LOGIC_VECTOR (4 downto 0);
           S : in STD_LOGIC_VECTOR (1 downto 0);
           dir : in STD_LOGIC;
           R : out STD_LOGIC_VECTOR (4 downto 0));
end combinational_shifter;

architecture Behavioral of combinational_shifter is

signal left_level1 : STD_LOGIC_VECTOR (4 downto 0);
signal left_level2 : STD_LOGIC_VECTOR (4 downto 0);
signal right_level1 : STD_LOGIC_VECTOR (4 downto 0);
signal right_level2 : STD_LOGIC_VECTOR (4 downto 0);

begin
    left_level1 <= A when s(0)='0' else A(3 downto 0) & "0";
    left_level2 <= left_level1 when s(1)='0' else left_level1(2 downto 0) & "00";
    
    right_level1 <= A when s(1)='0' else A(4) & A(4 downto 1);
    right_level2 <= right_level1 when s(0)='0' else right_level1(4) & right_level1(4) & right_level1(4 downto 2);
    
    R <= left_level2 when dir='0' else right_level2;
    
    
end Behavioral;

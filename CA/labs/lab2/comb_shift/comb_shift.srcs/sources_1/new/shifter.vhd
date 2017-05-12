----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/14/2017 10:25:04 PM
-- Design Name: 
-- Module Name: shifter - Behavioral
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

entity shifter is
         Port ( 
         number:in std_logic_vector(4  downto 0);
         sh: in std_logic_vector(1 downto 0);
         dir: in std_logic;
         res: out std_logic_vector(4 downto 0)
            
         );
end shifter;

architecture Behavioral of shifter is
signal left_partial: std_logic_vector(4 downto 0);
signal left_final: std_logic_vector(4 downto 0);
signal right_partial: std_logic_vector(4 downto 0);
signal right_final: std_logic_vector(4 downto 0);
begin
left_partial <= number when sh(0)='0' else number(3 downto 0) & "0";
left_final <=left_partial when sh(1)='0' else left_partial(2 downto 0) & "00";
right_partial <= number when sh(0)='0' else number(4)&number(4 downto 1);
right_final <=right_partial when sh(1)='0' else number(4)&number(4)&number(4 downto 2);

res <= right_final when dir ='1' else left_final;

end Behavioral;

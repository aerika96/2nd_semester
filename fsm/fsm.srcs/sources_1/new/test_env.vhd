----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04/28/2017 03:43:57 AM
-- Design Name: 
-- Module Name: test_env - Behavioral
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

entity test_env is
    Port ( clk : in STD_LOGIC;
           rx: in STD_LOGIC;
           btn : in STD_LOGIC_VECTOR (4 downto 0);
           sw : in STD_LOGIC_VECTOR (15 downto 0);
           led : out STD_LOGIC_VECTOR (14 downto 0);
           an : out STD_LOGIC_VECTOR (3 downto 0);
           cat : out STD_LOGIC_VECTOR (6 downto 0);
           tx: out STD_LOGIC
           );
           
           
end test_env;

architecture Behavioral of test_env is

signal baud_en: std_logic:='0';
signal int_count: std_logic_vector(15 downto 0):=(others=>'0');
begin
process(clk)
begin
    if(rising_edge(clk)) then
    int_count<=int_count+1;
    end if;
    if(int_count="0010100010110000")then
        baud_en<='1';
    else baud_en<='0';    
    end if;
    if(int_count="0010100010110001") then
    int_count<=(others =>'0');
    end if;
end process;


end Behavioral;

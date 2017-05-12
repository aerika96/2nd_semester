----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/03/2017 08:20:42 AM
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
           btn : in STD_LOGIC_VECTOR (4 downto 0);
           sw : in STD_LOGIC_VECTOR (15 downto 0);
           led : out STD_LOGIC_VECTOR (15 downto 0);
           an : out STD_LOGIC_VECTOR (3 downto 0);
           cat : out STD_LOGIC_VECTOR (6 downto 0));
end test_env;

architecture Behavioral of test_env is
component mpg 
    Port ( clk : in STD_LOGIC;
           button : in STD_LOGIC;
           en : out STD_LOGIC);
end component;

signal count : std_logic_vector (15 downto 0) := (others => '0');
signal int_en : std_logic:='0';
signal int_count: std_logic_vector(15 downto 0) := (others =>'0');
begin

led <= count;
an <= btn(3 downto 0);
cat <= (others=>'0');
    process(clk, int_en)
    begin
    
    if(rising_edge(clk)) then
        if(int_en='1')then
        count <= count+1;
        end if;
    end if;   
    end process;    

    mono_pulse : mpg port map (clk,btn(4),int_en);
    

end Behavioral;

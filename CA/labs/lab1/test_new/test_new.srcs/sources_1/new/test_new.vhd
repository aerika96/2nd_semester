----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/08/2017 07:46:17 PM
-- Design Name: 
-- Module Name: test_new - Behavioral
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

entity test_new is
    Port ( clk : in STD_LOGIC;
           btn : in STD_LOGIC_VECTOR (4 downto 0);
           sw : in STD_LOGIC_VECTOR (15 downto 0);
           led : out STD_LOGIC_VECTOR (15 downto 0);
           an : out STD_LOGIC_VECTOR (3 downto 0);
           cat : out STD_LOGIC_VECTOR (6 downto 0));
end test_new;

architecture Behavioral of test_new is

component mpg is
    Port ( clk : in STD_LOGIC;
           button : in STD_LOGIC_VECTOR(3 downto 0);
           en : out STD_LOGIC);
end component;

signal count:std_logic_vector(2 downto 0) := (others => '0');
signal int_en:std_logic:='0';
signal output:std_logic_vector(7 downto 0):=(others => '0');

begin

mono_pulse: mpg port map (clk,btn(3 downto 0),int_en);

process(clk,int_en)
begin
if(rising_edge(clk)) then
    if(int_en = '1') then
    count <= count +1;
    end if;
  end if;
end process;

process(count)
begin
    case count is
        when "000" => led(6 downto 0)<="0000000";
        when "001" => led(6 downto 0)<="0000001";
        when "010" => led(6 downto 0)<="0000010";
        when "011" => led(6 downto 0)<="0000100";
        when "100" => led(6 downto 0)<="0001000";
        when "101" => led(6 downto 0)<="0010000";
        when "110" => led(6 downto 0)<="0100000";
        when "111" => led(6 downto 0)<="1000000";
     end case;
 end process;    
     

end Behavioral;

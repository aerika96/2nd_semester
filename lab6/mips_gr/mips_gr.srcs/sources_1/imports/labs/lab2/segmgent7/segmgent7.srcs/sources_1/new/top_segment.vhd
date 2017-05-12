----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/10/2017 07:07:30 AM
-- Design Name: 
-- Module Name: top_segment - Behavioral
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

entity top_segment is
Port ( clk : in STD_LOGIC;
        an : out STD_LOGIC_VECTOR (3 downto 0);
        cat : out STD_LOGIC_VECTOR (6 downto 0);
        led :out STD_LOGIC_VECTOR(15 downto 0 );
        sw: in STD_LOGIC_VECTOR(15 downto 0);
        btn:in STD_LOGIC_VECTOR(4 downto 0)
        );
end top_segment;

architecture Behavioral of top_segment is

component segment7 is
    Port ( clk : in STD_LOGIC;
           digit0 : in STD_LOGIC_VECTOR(3 downto 0);
           digit1 : in STD_LOGIC_VECTOR(3 downto 0);
           digit2 : in STD_LOGIC_VECTOR(3 downto 0);
           digit3 : in STD_LOGIC_VECTOR(3 downto 0);
           an : out STD_LOGIC_VECTOR (3 downto 0);
           cat : out STD_LOGIC_VECTOR (6 downto 0));
end component;

component mpg is
    Port ( clk : in STD_LOGIC;
           button : in STD_LOGIC_VECTOR (3 downto 0);
           en : out STD_LOGIC);
end component;

signal first : std_logic_vector(15 downto 0);
signal second : std_logic_vector(15 downto 0);
signal result : std_logic_vector(15 downto 0);
signal shift_operand:std_logic_vector (15 downto 0);
signal add_result : std_logic_vector(15 downto 0);
signal sub_result : std_logic_vector(15 downto 0);
signal shift_left_result : std_logic_vector(15 downto 0);
signal shift_right_result : std_logic_vector(15 downto 0);
signal int_en:std_logic;
signal int_count: std_logic_vector(1 downto 0) := (others=>'0');
signal d1:std_logic;

begin
segment : segment7 port map (clk,result(3 downto 0),result(7 downto 4),result(11 downto 8),result(15 downto 12),an,cat);
mpg1: mpg port map(clk,btn(3 downto 0),int_en);
process (clk, int_en)
begin
if(rising_edge(clk)) then
    if(int_en ='1') then
    int_count <= int_count+1;
     end if;
   end if;  
end process;

process(int_count,clk)
begin
case int_count is 
when "00" => result <= add_result;
when "01" => result <= sub_result;
when "10" => result <= shift_left_result;
when others => result <= shift_right_result;
end case;
end process;
first<="000000000000" & sw(3 downto 0);
second<="000000000000" & sw(7 downto 4);
shift_operand <= "00000000" & sw(7 downto 0);
add_result <= first + second;
sub_result <= second - first;
shift_left_result <= shift_operand(13 downto 0)&"00";
shift_right_result <= "00" & shift_operand(15 downto 2);

led(15 downto 14) <= int_count;
led(7) <= '1' when result = "0000000000000000" else '0';

end Behavioral;

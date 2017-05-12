----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/05/2017 12:17:07 PM
-- Design Name: 
-- Module Name: seven_seg - Behavioral
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

entity seven_seg is
    Port ( Digit0 : in STD_LOGIC_VECTOR (3 downto 0);
           Digit1 : in STD_LOGIC_VECTOR (3 downto 0);
           Digit2 : in STD_LOGIC_VECTOR (3 downto 0);
           Digit3 : in STD_LOGIC_VECTOR (3 downto 0);   
           CAT : out STD_LOGIC_VECTOR (6 downto 0);
           clk : in STD_LOGIC;
           AN : out STD_LOGIC_VECTOR (3 downto 0));
end seven_seg;

architecture Behavioral of seven_seg is

signal cnt : std_logic_vector (15 downto 0);
signal hex : std_logic_vector (3 downto 0);

begin

    process(clk)
    begin
        if rising_edge(clk) then
            cnt <= cnt + 1;
        end if;
    end process;

    process(cnt(15 downto 14), Digit0, Digit1, Digit2, Digit3)
    begin
        case cnt(15 downto 14) is
            when "00" => hex <= Digit0;
            when "01" => hex <= Digit1;
            when "10" => hex <= Digit2;
            when "11" => hex <= Digit3;
            when others => hex <= "0000";
        end case;
    end process;
    
    process(cnt(15 downto 14))
        begin
            case cnt(15 downto 14) is
                when "00" => an <= "1110";
                when "01" => an <= "1101";
                when "10" => an <= "1011";
                when "11" => an <= "0111";
                when others => an <= "1111";
            end case;
        end process;
    
    with hex SELect
           CAT<= "1111001" when "0001",   --1
                 "0100100" when "0010",   --2
                 "0110000" when "0011",   --3
                 "0011001" when "0100",   --4
                 "0010010" when "0101",   --5
                 "0000010" when "0110",   --6
                 "1111000" when "0111",   --7
                 "0000000" when "1000",   --8
                 "0010000" when "1001",   --9
                 "0001000" when "1010",   --A
                 "0000011" when "1011",   --b
                 "1000110" when "1100",   --C
                 "0100001" when "1101",   --d
                 "0000110" when "1110",   --E
                 "0001110" when "1111",   --F
                 "1000000" when others;   --0
    
        

end Behavioral;

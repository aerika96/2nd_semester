----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/03/2017 08:15:56 AM
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
Port ( sw : in std_logic_vector(15 downto 0);
         btn : in std_logic_vector(4 downto 0);
         led : out std_logic_vector(15 downto 0);
         an : out std_logic_vector(3 downto 0);
         cat : out std_logic_vector(6 downto 0);
         clk : in std_logic
         );
end test_env;



architecture Behavioral of test_env is

signal cnt : std_logic_vector(1 downto 0) := (others=>'0');
signal en : std_logic;
signal d1 : std_logic;
signal result : std_logic_vector(15 downto 0);
signal first_operand : std_logic_vector(15 downto 0);
signal second_operand : std_logic_vector(15 downto 0);
signal shift_operand : std_logic_vector(15 downto 0);
signal add_result : std_logic_vector(15 downto 0);
signal subtr_result : std_logic_vector(15 downto 0);
signal shift_left_result : std_logic_vector(15 downto 0);
signal shift_right_result : std_logic_vector(15 downto 0);

component mpg is
    Port ( buttons : in STD_LOGIC_VECTOR(4 downto 0);
           clk : in STD_LOGIC;
           enable : out STD_LOGIC);
end component;

component seven_seg is
    Port ( Digit0 : in STD_LOGIC_VECTOR (3 downto 0);
           Digit1 : in STD_LOGIC_VECTOR (3 downto 0);
           Digit2 : in STD_LOGIC_VECTOR (3 downto 0);
           Digit3 : in STD_LOGIC_VECTOR (3 downto 0);
           CAT : out STD_LOGIC_VECTOR (6 downto 0);
           clk : in STD_LOGIC;
           AN : out STD_LOGIC_VECTOR (3 downto 0));
end component;



begin
    first_operand <= "000000000000" & sw(3 downto 0);
    second_operand <= "000000000000" & sw(7 downto 4);
    
    shift_operand <= "00000000" & sw(7 downto 0);

    mpg1 : mpg port map(buttons=>btn, clk=>clk, enable=>d1);
    seg1 : seven_seg port map(Digit0=>result(3 downto 0), Digit1=>result(7 downto 4), Digit2=>result(11 downto 8), 
                              Digit3=>result(15 downto 12), cat=>CAT,clk=>clk, an=>an);

    process (clk)
    begin
        if rising_edge(clk) then
            if d1='1' then
                cnt <= cnt + 1;
            end if;
        end if;
    end process;
    
    process (clk)
    begin
        case cnt is
            when "00" => result <= add_result;
            when "01" => result <= subtr_result;
            when "10" => result <= shift_left_result;
            when others => result <= shift_right_result;
        end case;
    end process;
    
    led(15 downto 14) <= cnt;
    
    led(7) <= '1' when result="0000000000000000" else '0';
    
    add_result <= first_operand + second_operand;
    subtr_result <= first_operand - second_operand;
    shift_left_result <= shift_operand(13 downto 0) & "00";
    shift_right_result <= "00" & shift_operand(15 downto 2);

end Behavioral;

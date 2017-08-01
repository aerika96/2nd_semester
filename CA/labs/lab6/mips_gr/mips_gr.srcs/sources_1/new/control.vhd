----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04/12/2017 10:17:26 AM
-- Design Name: 
-- Module Name: control - Behavioral
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity control is
 Port ( opcode : in std_logic_vector(2 downto 0);
        control_sig:out std_logic_vector(8 downto 0)
 );
end control;

architecture Behavioral of control is


begin

process(opcode)
begin
case(opcode)is
when "000" => control_sig<="111101000"; --r-type
when "001" => control_sig<="100011100"; --addi
when "010" => control_sig<="100010001"; --lw
when "011" => control_sig<="000010010"; --sw
when "100" => control_sig<="001000100"; --beq
when "101" => control_sig<="110011000"; --andi
when "110" => control_sig<="001000100"; --bgez
when "111" => control_sig<="000000000"; --jmp
when others => control_sig <= "111111111";
end case;

end process;
end Behavioral;

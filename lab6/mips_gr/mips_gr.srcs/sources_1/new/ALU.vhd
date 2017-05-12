----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04/13/2017 05:16:01 AM
-- Design Name: 
-- Module Name: ALU - Behavioral
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

entity ALU is
  Port (
        op1: in std_logic_vector(15 downto 0);
        op2: in std_logic_vector(15 downto 0);
        sa: in std_logic;
        func: in std_logic_vector(2 downto 0);
        aluop: in std_logic_vector(1 downto 0);
        result: out std_logic_vector(15 downto 0)
   );
end ALU;

architecture Behavioral of ALU is

signal use_func: std_logic:='0';
signal int_res: std_logic_vector(15 downto 0):=(others=>'0');
begin
process(aluop)
begin
case (aluop) is
when "11" =>
case (func)is
when "000" => int_res<=op1+op2;
when "001" => int_res<=op1-op2;
when "010" =>
 if(sa='1') then
    int_res<=op1(14 downto 0)&'0' ;
 else int_res <=op1;
 end if;
when "011" =>
if(sa='1') then
    int_res<='0'&op1(15 downto 1);
else int_res <=op1;
end if;
when "100" => int_res<=op1 and op2;
when "101" => int_res<=op1 or op2;
when "110" => int_res<=op1 xor op2;
when "111" => 
if(sa='1') then
    if(op1(15)='1')then
    int_res<='1'&op1(15 downto 1);
    else 
    int_res<='0'& op1(15 downto 1);
    end if;
else int_res <=op1;
end if;
when others => int_res <= (others=>'0');
end case;
when "00" => int_res<=op1+op2;
when "01" =>int_res <= op1-op2;
when "10" =>int_res <= op1 and op2;
when others =>int_res <= (others=>'1');
end case;
end process;

result<=int_res;

end Behavioral;

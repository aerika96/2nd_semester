----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/30/2017 06:43:31 PM
-- Design Name: 
-- Module Name: mips_top - Behavioral
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

entity mips_top is
    Port ( clk : in STD_LOGIC;
            enable : in STD_LOGIC;
            beq : in STD_LOGIC;
            jmp : in STD_LOGIC;
           instruction:out STD_LOGIC_VECTOR(15 downto 0)
    );
end mips_top;

architecture Behavioral of mips_top is
signal addr:std_logic_vector(15 downto 0) := (others=>'0');
signal addr_out:std_logic_vector(15 downto 0):=(others=>'0');
signal int_addr:std_logic_vector(15 downto 0):=(others=>'0');
signal final_addr:std_logic_vector(15 downto 0):=(others=>'0');
signal beqAddr:std_logic_vector(15 downto 0):="0000000000000011";
signal jmpAddr:std_logic_vector(15 downto 0):="0000000000000111";
 
signal int_display:std_logic_vector(15 downto 0);
signal int_display_final:std_logic_vector(15 downto 0);
component rom 
    Port(
        address: in std_logic_vector(3 downto 0);
        output : out std_logic_vector(15 downto 0)
    );
end component;

begin

addr<=addr_out+1;
int_addr<=addr when beq='0' else beqAddr;
final_addr<=int_addr when jmp='0' else jmpAddr;

process(clk,enable)
begin
if(rising_edge(clk)) then
    if(enable='1') then
    addr_out<=final_addr;
    end if;
end if;
end process;

rom_memory: rom port map (addr_out(3 downto 0),int_display);
end Behavioral;

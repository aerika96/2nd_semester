----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04/12/2017 10:01:43 AM
-- Design Name: 
-- Module Name: mips_gr - Behavioral
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

entity mips_gr is
    Port ( clk : in STD_LOGIC;
           btn : in STD_LOGIC_VECTOR (4 downto 0);
           sw : in STD_LOGIC_VECTOR (15 downto 0);
           led : out STD_LOGIC_VECTOR (15 downto 0);
           an : out STD_LOGIC_VECTOR (3 downto 0);
           cat : out STD_LOGIC_VECTOR (6 downto 0));
end mips_gr;

architecture Behavioral of mips_gr is

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

component control 
 Port ( opcode : in std_logic_vector(2 downto 0);
        control_sig:out std_logic_vector(8 downto 0)
 );
end component;

component inst_data 
  Port ( 
    clk:in std_logic;
    instruction: in std_logic_vector (15 downto 0);
    write_data: in std_logic_vector (15 downto 0);
    contr: in std_logic_vector(8 downto 0);
    enable : in std_logic;
    rd1 : out std_logic_vector (15 downto 0);
    rd2 : out std_logic_vector (15 downto 0)
  );
end component;

component mips_top 
    Port ( clk : in STD_LOGIC;
            enable : in STD_LOGIC;
            beq : in STD_LOGIC;
            jmp : in STD_LOGIC;
           instruction:out STD_LOGIC_VECTOR(15 downto 0)
    );
end component;

signal int_en: std_logic;
signal instr: std_logic_vector(15 downto 0);
signal int_control: std_logic_vector(8 downto 0);
signal write_dat: std_logic_vector(15 downto 0):= (others=>'0');
signal int_rd1 : std_logic_vector(15 downto 0);
signal int_rd2: std_logic_vector(15 downto 0);
signal int_display:std_logic_vector(15 downto 0);
begin

mono_pulse : mpg  port map (clk, btn(3 downto 0),int_en);
inst_fetch : mips_top port map(clk,int_en,'0','0',instr);
main_control : control port map(instr (15 downto 13),int_control);
instr_data : inst_data port map (clk,instr,write_dat,int_control,int_en,int_rd1,int_rd2);
write_dat<=int_rd1+int_rd2;
seg_7:segment7 port map (clk,int_display(15 downto 12),int_display(11 downto 8), int_display(7 downto 4),int_display(3 downto 0),an,cat);

process(sw(7 downto 5))
begin
case(sw(7 downto 5)) is
when "000"=> int_display<=instr;
when "010"=> int_display<=write_dat;
when "100"=> int_display<= (others =>'0');
when others =>int_display<= (others =>'0');
end case;
end process;

end Behavioral;

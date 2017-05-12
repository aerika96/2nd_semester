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
           button : in STD_LOGIC;
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
    rd2 : out std_logic_vector (15 downto 0);
    ext_imm: out std_logic_vector (15 downto 0)
  );
end component;

component mips_top 
    Port ( clk : in STD_LOGIC;
            enable : in STD_LOGIC;
            beq : in STD_LOGIC;
            beqz:in STD_LOGIC;
            jmp : in STD_LOGIC;
            beq_address: in STD_LOGIC_VECTOR(15 downto 0);
            beqz_address: in STD_LOGIC_VECTOR(15 downto 0);
            jmp_address: in STD_LOGIC_VECTOR(15 DOWNTO 0);
            address : out STD_LOGIC_VECTOR(15 downto 0);
           instruction:out STD_LOGIC_VECTOR(15 downto 0)
    );
end component;

component exec_unit 
 Port ( 
    pc_4: in std_logic_vector (15 downto 0);
    rd1 : in std_logic_vector(15 downto 0);
    rd2 : in std_logic_vector(15 downto 0);
    ext_imm : in std_logic_vector(15 downto 0);
    func : in std_logic_vector(2 downto 0);
    sa: in std_logic;
    alusrc: in std_logic;
    aluop:in std_logic_vector(1 downto 0);
    branch:out std_logic_vector(15 downto 0);
    result: out std_logic_vector(15 downto 0);
    zero: out std_logic
 );
end component;
component data_memory 
  Port ( 
    clk:in std_logic;
    address: in std_logic_vector(15 downto 0);
    re:in std_logic;
    we: in std_logic;
    write_data: in std_logic_vector(15 downto 0);
    address_content:out std_logic_vector(15 downto 0);
    output:out std_logic_vector(15 downto 0)
  );
end component;

signal int_en: std_logic;
signal int_en1:std_logic;
signal instr: std_logic_vector(15 downto 0);
signal int_control: std_logic_vector(8 downto 0);
signal write_dat: std_logic_vector(15 downto 0):= (others=>'0');
signal int_rd1 : std_logic_vector(15 downto 0);
signal int_rd2: std_logic_vector(15 downto 0):=(others=>'0');
signal int_display:std_logic_vector(15 downto 0);
signal int_address: std_logic_vector(15 downto 0);
signal int_ext_imm : std_logic_vector(15 downto 0);
signal int_branch: std_logic_vector(15 downto 0):=(others=>'0');
signal int_result: std_logic_vector(15 downto 0):=(others=>'0');
signal int_zero: std_logic;
signal int_pc_4:std_logic_vector(15 downto 0);
signal write_from_memory: std_logic_vector(15 downto 0):=(others=>'0');
signal final_write:std_logic_vector(15 downto 0):=(others=>'0');
signal branch:std_logic;
signal jump:std_logic;
signal beqz: std_logic;
signal int_jump:std_logic_vector(15 downto 0):=(others=>'0');
signal write_reg: std_logic_vector(2 downto 0);
signal memory_content:std_logic_vector(15 downto 0);
signal beqz_address: std_logic_vector(15 downto 0);
begin

mono_pulse : mpg  port map (clk, btn(3),int_en);
mono_pulse1 : mpg  port map (clk, btn(2),int_en1);
int_jump<="000"&instr(12 downto 0);
inst_fetch : mips_top port map(clk,int_en,branch,beqz,jump,int_branch,beqz_address,int_jump,int_address,instr);
main_control : control port map(instr (15 downto 13),int_control);
instr_data : inst_data port map (clk,instr,final_write,int_control,int_en1,int_rd1,int_rd2, int_ext_imm);
seg_7:segment7 port map (clk,int_display(3 downto 0),int_display(7 downto 4), int_display(11 downto 8),int_display(15 downto 12),an,cat);
int_pc_4<=int_address+1;
beqz_address<=int_address+1+int_ext_imm;
execution: exec_unit port map(int_pc_4,int_rd1,int_rd2,int_ext_imm,instr(2 downto 0),instr(3),int_control(4),int_control(7 downto 6),int_branch,int_result,int_zero);
dat_mem: data_memory port map(clk,int_result,int_control(0), int_control(1),int_rd2,memory_content,write_from_memory);
final_write<=int_result when int_control(3)='1' else write_from_memory;
branch<=int_zero and instr(15) and not(instr(14)) and not(instr(13));
jump<=instr(15) and instr(14) and instr(13);
beqz<=not int_result(15)and instr(15) and instr(14) and not(instr(13));
process(sw(9 downto 5))
begin
case(sw(7 downto 5)) is
when "000"=> int_display<=instr;
when "001"=> int_display<=int_address+1;
when "010"=> int_display<=int_rd1;
when "011"=> int_display<= int_rd2;
when "100"=> int_display<=int_ext_imm;
when "101" => int_display<=int_result;
when "110" =>int_display<=memory_content;
when "111" =>int_display<=final_write;
when others =>int_display<= (others =>'0');
end case;
end process;

end Behavioral;

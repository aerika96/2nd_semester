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
      destination: in std_logic_vector(2 downto 0);
      ext: in std_logic;
      enable : in std_logic;
      reg_wr: in std_logic;
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
     regdest: in std_logic;
     rt: in std_logic_vector(2 downto 0);
     rd: in std_logic_vector(2 downto 0);
     branch:out std_logic_vector(15 downto 0);
     result: out std_logic_vector(15 downto 0);
     zero: out std_logic;
     destination : out std_logic_vector(2 downto 0)
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

component register_if_id 
  Port ( clk: in std_logic;
         enable: in std_logic;
          pc4: in std_logic_vector(15 downto 0);
          instr: in std_logic_vector(15 downto 0);
          pc4_out:out std_logic_vector(15 downto 0);
          instr_out: out std_logic_vector(15 downto 0)
  );
end component;

component reg_id_ex 
  Port (clk:in std_logic;
        enable: in std_logic;
        wb_in: in std_logic_vector(1 downto 0);
        m_in:in std_logic_vector(2 downto 0);
        ex_in: in std_logic_vector(3 downto 0);
        pc4_in:in std_logic_vector(15 downto 0);
        rd1_in:in std_logic_vector(15 downto 0);
        rd2_in:in std_logic_vector(15 downto 0);
        immed_in:in std_logic_vector(15 downto 0);
        func_in: in std_logic_vector(2 downto 0);
        rt_in: in std_logic_vector(2 downto 0);
        rd_in: in std_logic_vector(2 downto 0);
        sa_in: in std_logic;
        wb_out: out std_logic_vector(1 downto 0);
        m_out: out std_logic_vector(2 downto 0);
        ex_out:out std_logic_vector(3 downto 0);
        pc4_out:out std_logic_vector(15 downto 0);
        rd1_out:out std_logic_vector(15 downto 0);
        rd2_out:out std_logic_vector(15 downto 0);
        immed_out:out std_logic_vector(15 downto 0);
        func_out: out std_logic_vector(2 downto 0);
        rt_out: out std_logic_vector(2 downto 0);
        rd_out: out std_logic_vector(2 downto 0);
        sa_out: out std_logic
        );
end component;


component reg_ex_mem 
  Port ( clk: in std_logic;
         enable : in std_logic;
         wb_in: std_logic_vector(1 downto 0);
         m_in: std_logic_vector(2 downto 0);
         branch_in:std_logic_vector(15 downto 0);
         zero: in std_logic;
         result: in std_logic_vector(15 downto 0);
         rd2:in std_logic_vector(15 downto 0);
         reg_dest: in std_logic_vector(2 downto 0);
         wb_out:out std_logic_vector(1 downto 0);
         m_out:out std_logic_vector(2 downto 0);
         branch_out: out std_logic_vector(15 downto 0);
         zero_out: out std_logic;
         result_out: out std_logic_vector(15 downto 0);
         rd2_out:out std_logic_vector(15 downto 0);
         reg_dest_out: out std_logic_vector(2 downto 0)
      );
end component;

component reg_mem_wb 
  Port ( 
    clk:in std_logic;
    enable: in std_logic;
    wb_in: in std_logic_vector(1 downto 0);
    regcont_in: in std_logic_vector(15 downto 0);
    memcont_in:in std_logic_vector(15 downto 0);
    regdest_in: in std_logic_vector(2 downto 0);
    wb_out: out std_logic_vector(1 downto 0);
    regcont_out: out std_logic_vector(15 downto 0);
    memcont_out: out std_logic_vector (15 downto 0);
    regdest_out: out std_logic_vector (2 downto 0)
    
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
signal pc4_reg: std_logic_vector(15 downto 0);
signal instr_regifid:std_logic_vector(15 downto 0);
signal branch_op: std_logic;
signal branchgr_op:std_logic;
signal zero_outexmem:std_logic;
signal wb_inidex,wb_outidex,wb_inexmem,wb_outexmem,wb_outmemwb: std_logic_vector(1 downto 0);
signal m_outidex,m_inidex,func_outidex,rd_outidex,rt_outidex,regdest_outexmem,m_outexmem,regdest_outmemwb: std_logic_vector(2 downto 0);
signal rd1_outidex,rd2_outidex,immed_outidex,pc4_outidex,branch_outexmem,result_outexmem,rd2_outexmem,result_outmemwb,memcont_outmemwb: std_logic_vector(15 downto 0);
signal sa_outidex: std_logic;
signal ex_inidex,ex_outidex: std_logic_vector(3 downto 0);
signal regdest:std_logic_vector(2 downto 0);
begin

mono_pulse : mpg  port map (clk, btn(3),int_en);
mono_pulse1 : mpg  port map (clk, btn(2),int_en1);
int_jump<="000"&instr_regifid(12 downto 0);
inst_fetch : mips_top port map(clk,int_en,branch,beqz,jump,branch_outexmem,branch_outexmem,int_jump,int_address,instr);
reg_if_id: register_if_id port map (clk,int_en,int_pc_4,instr,pc4_reg,instr_regifid);
main_control : control port map(instr_regifid (15 downto 13),int_control);
instr_data : inst_data port map (clk,instr_regifid,final_write,regdest_outmemwb,int_control(2),int_en1,wb_outmemwb(0),int_rd1,int_rd2, int_ext_imm);
branch_op<=instr_regifid(15) and not(instr_regifid(14)) and not(instr_regifid(13));
branchgr_op<=instr_regifid(15) and instr_regifid(14) and not(instr_regifid(13));
wb_inidex<=int_control(3)&int_control(8);
m_inidex<=instr_regifid(1)&branch_op&branchgr_op;
ex_inidex<=int_control(7 downto 6)&int_control(4)&int_control(5);
reg_idex: reg_id_ex port map (clk,int_en,wb_inidex,m_inidex,ex_inidex,pc4_reg,int_rd1,int_rd2,int_ext_imm,instr_regifid(2 downto 0),instr_regifid(9 downto 7),instr_regifid(6 downto 4),instr_regifid(3),wb_outidex,m_outidex,ex_outidex,pc4_outidex,rd1_outidex,rd2_outidex,immed_outidex,func_outidex,rt_outidex,rd_outidex,sa_outidex);
seg_7:segment7 port map (clk,int_display(3 downto 0),int_display(7 downto 4), int_display(11 downto 8),int_display(15 downto 12),an,cat);
int_pc_4<=int_address+1;
beqz_address<=int_address+1+int_ext_imm;
execution: exec_unit port map(pc4_reg,rd1_outidex,rd2_outidex,immed_outidex,func_outidex,sa_outidex,ex_outidex(1),ex_outidex(3 downto 2),ex_outidex(0),rt_outidex,rd_outidex,int_branch,int_result,int_zero,regdest);
reg_exmem : reg_ex_mem port map(clk,int_en,wb_outidex,m_outidex,int_branch,int_zero,int_result,rd2_outidex,regdest,wb_outexmem,m_outexmem,branch_outexmem,zero_outexmem,result_outexmem,rd2_outexmem,regdest_outexmem);
dat_mem: data_memory port map(clk,result_outexmem,'1', m_outexmem(2),rd2_outexmem,memory_content,write_from_memory);
reg_memwb : reg_mem_wb port map(clk,int_en,wb_outexmem,result_outexmem,write_from_memory,regdest_outexmem,wb_outmemwb,result_outmemwb,memcont_outmemwb,regdest_outmemwb);
final_write<=result_outmemwb when wb_outmemwb(1)='1' else memcont_outmemwb;
branch<=zero_outexmem and instr_regifid(15) and not(instr_regifid(14)) and not(instr_regifid(13));
jump<=instr_regifid(15) and instr_regifid(14) and instr_regifid(13);
beqz<=not result_outmemwb(15)and instr_regifid(15) and instr_regifid(14) and not(instr_regifid(13));
process(sw(9 downto 5))
begin
case(sw(7 downto 5)) is
when "000"=> int_display<=instr_regifid;
when "001"=> int_display<=int_address+1;
when "010"=> int_display<=rd1_outidex;
when "011"=> int_display<= rd2_outidex;
when "100"=> int_display<=int_ext_imm;
when "101" => int_display<=result_outmemwb;
when "110" =>int_display<=memcont_outmemwb;
when "111" =>int_display<=final_write;
when others =>int_display<= (others =>'0');
end case;
end process;

end Behavioral;

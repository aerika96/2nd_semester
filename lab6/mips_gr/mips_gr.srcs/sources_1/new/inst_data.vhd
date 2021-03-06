----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04/12/2017 12:10:53 PM
-- Design Name: 
-- Module Name: inst_data - Behavioral
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

entity inst_data is
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
end inst_data;

architecture Behavioral of inst_data is

component regf 
  Port ( 
    clk:in std_logic;
    regwr: in std_logic;
    ra1: in std_logic_vector(2 downto 0);
    ra2: in std_logic_vector(2 downto 0);
    wa : in std_logic_vector(2 downto 0);
    wd : in std_logic_vector (15 downto 0);
    rd1 : out std_logic_vector (15 downto 0);
    rd2 : out std_logic_vector (15 downto 0)
  );
end component;
signal int_regwr: std_logic;
signal int_dest: std_logic_vector(2 downto 0);
signal int_imm: std_logic_vector(15 downto 0);
signal int_rd2 : std_logic_vector(15 downto 0);
signal extended : std_logic_vector(15 downto 0);
begin
int_imm <= "111111111"&instruction(6 downto 0) when instruction(6)='1' else "000000000"&instruction(6 downto 0);
int_regwr <= reg_wr;
extended<=int_imm when ext='1' else "000000000"&instruction(6 downto 0);
ext_imm<=extended;
int_dest<=destination;
regist_file: regf port map (clk,int_regwr,instruction(12 downto 10),instruction(9 downto 7),int_dest,write_data,rd1,int_rd2);
rd2<= int_rd2 ;
end Behavioral;

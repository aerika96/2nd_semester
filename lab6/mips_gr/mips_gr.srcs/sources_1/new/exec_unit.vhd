----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04/13/2017 05:18:32 AM
-- Design Name: 
-- Module Name: exec_unit - Behavioral
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

entity exec_unit is
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
end exec_unit;

architecture Behavioral of exec_unit is

component ALU 
  Port (
        op1: in std_logic_vector(15 downto 0);
        op2: in std_logic_vector(15 downto 0);
        sa: in std_logic;
        func: in std_logic_vector(2 downto 0);
        aluop: in std_logic_vector(1 downto 0);
        result: out std_logic_vector(15 downto 0)
   );
end component;

signal int_result: std_logic_vector(15 downto 0);
signal shift_imm: std_logic_vector(15 downto 0);
signal int_rd2 : std_logic_vector(15 downto 0);
begin

int_rd2<=ext_imm when alusrc='1' else rd2;
ar_logic_unit: ALU port map (rd1,int_rd2,sa,func,aluop,int_result);
zero <= '1' when int_result = "0000000000000000" else '0';
result<=int_result;
shift_imm<=ext_imm(15 downto 1);
branch <= shift_imm+pc_4;



end Behavioral;

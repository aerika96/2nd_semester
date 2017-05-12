----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04/28/2017 03:43:57 AM
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
    Port ( clk : in STD_LOGIC;
           rx: in STD_LOGIC;
           btn : in STD_LOGIC_VECTOR (4 downto 0);
           sw : in STD_LOGIC_VECTOR (15 downto 0);
           led : out STD_LOGIC_VECTOR (14 downto 0);
           an : out STD_LOGIC_VECTOR (3 downto 0);
           cat : out STD_LOGIC_VECTOR (6 downto 0);
           tx: out STD_LOGIC
           );
           
           
end test_env;

architecture Behavioral of test_env is
component tx_fsm 
  Port (
    clk: in std_logic;
    tx_dat:in std_logic_vector(7 downto 0);
    tx_en: in std_logic;
    rst: in std_logic;
    baud_en: in std_logic;
    tx:out std_logic;
    tx_rdy: out std_logic
   );
end component;

component mpg 
    Port ( clk : in STD_LOGIC;
           button : in STD_LOGIC;
           en : out STD_LOGIC);
end component;
signal int_en1: std_logic;
signal int_en2:std_logic; 
signal baud_en: std_logic:='0';
signal int_count: std_logic_vector(15 downto 0):=(others=>'0');
signal int_tx: std_logic;
begin
process(clk)
begin
    if(rising_edge(clk)) then
    int_count<=int_count+1;
    end if;
    if(int_count="0010100010110000")then
        baud_en<='1';
    else baud_en<='0';    
    end if;
    if(int_count="0010100010110001") then
    int_count<=(others =>'0');
    end if;
end process;
mpg1: mpg port map (clk, btn(0),int_en1);
mpg2: mpg port map(clk, btn(1),int_en2);
fin_state_mach : tx_fsm port map(clk,sw(7 downto 0),int_en1,int_en2,int_tx,led(8));
tx<=int_tx;
led(7 downto 0 )<=sw(7 downto 0);

end Behavioral;

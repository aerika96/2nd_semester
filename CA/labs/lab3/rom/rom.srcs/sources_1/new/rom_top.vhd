----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/17/2017 06:29:06 AM
-- Design Name: 
-- Module Name: rom_top - Behavioral
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

entity rom_top is
    Port ( clk : in STD_LOGIC;
           btn : in STD_LOGIC_VECTOR (4 downto 0);
           sw : in STD_LOGIC_VECTOR (15 downto 0);
           led : out STD_LOGIC_VECTOR (15 downto 0);
           an : out STD_LOGIC_VECTOR (3 downto 0);
           cat : out STD_LOGIC_VECTOR (6 downto 0));
end rom_top;

architecture Behavioral of rom_top is

component mpg is
    Port ( clk : in STD_LOGIC;
           button : in STD_LOGIC;
           en : out STD_LOGIC);
end component;

component segment7 is
    Port ( clk : in STD_LOGIC;
           digit0 : in STD_LOGIC_VECTOR(3 downto 0);
           digit1 : in STD_LOGIC_VECTOR(3 downto 0);
           digit2 : in STD_LOGIC_VECTOR(3 downto 0);
           digit3 : in STD_LOGIC_VECTOR(3 downto 0);
           an : out STD_LOGIC_VECTOR (3 downto 0);
           cat : out STD_LOGIC_VECTOR (6 downto 0));
end component;
component ram is 
port (  clk    : in std_logic; 
we   : in std_logic; 
en    : in std_logic; 
addr  : in std_logic_vector(7 downto 0); 
di    : in std_logic_vector(15 downto 0); 
do    : out std_logic_vector(15 downto 0)); 
end component; 

signal count:std_logic_vector (7 downto 0) := (others => '0');
signal en:std_logic;
signal int_en1:std_logic:='0';
signal wr_en:std_logic;

signal display:std_logic_vector(15 downto 0);

signal int_write:std_logic_vector(15 downto 0) :=(others => '0');
signal read1 :std_logic_vector(15 downto 0);
signal read2:std_logic_vector(15 downto 0);
type mem is array  (0 to 255)of std_logic_vector(15 downto 0);
signal ram_m : mem := (
    x"0001",
    x"0002",
    x"0003",
    x"0004",
    x"0005",
    x"0006",
    x"000A",
    x"000B" ,
    others => x"ABCD"   
);

begin
mono_p1: mpg port map(clk,btn(3),int_en1);

int_write<=read1(13 downto 0)&"00";
display<=int_write when sw(1)='1' else read1; 

en <= int_en1 when sw(0)='1' else '0';
wr_en <= int_en1 when sw(0)='0' else '0';

process (int_en1, clk)
begin
    if(rising_edge(clk)) then
        if(en='1') then
        count<=count+1;
        end if;
    end if; 
end process;  

ram_mem: ram port map (clk, wr_en,'1',count,int_write,read1);

 
 segment_7: segment7 port map(clk,display(3 downto 0),display(7 downto 4),display(11 downto 8),display(15 downto 12),an,cat);  
led(7 downto 0 )<=count;
    


end Behavioral;

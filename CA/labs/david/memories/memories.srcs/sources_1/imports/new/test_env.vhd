----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/03/2017 08:15:56 AM
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
Port ( sw : in std_logic_vector(15 downto 0);
         btn : in std_logic_vector(4 downto 0);
         led : out std_logic_vector(15 downto 0);
         an : out std_logic_vector(3 downto 0);
         cat : out std_logic_vector(6 downto 0);
         clk : in std_logic
         );
end test_env;



architecture Behavioral of test_env is

signal cnt : std_logic_vector(7 downto 0) := (others=>'0');

signal en : std_logic;
signal d1 : std_logic := '0';
signal d2 : std_logic;

--type memory is array (0 to 255) of std_logic_vector (15 downto 0);
--signal rom : memory := (
--    x"0000",
--    x"F001",
--    x"ABCD",
--    x"0002",
--    x"0303",
--    x"0404",
--    x"5005",
--    others => x"0000"
--    );

signal to_display : std_logic_vector (15 downto 0);

component mpg is
    Port ( button : in STD_LOGIC;
           clk : in STD_LOGIC;
           enable : out STD_LOGIC);
end component;


component reg_file is
port (
    clk : in std_logic;
    ra1 : in std_logic_vector (3 downto 0);
    ra2 : in std_logic_vector (3 downto 0);
    wa : in std_logic_vector (3 downto 0);
    wd : in std_logic_vector (15 downto 0);
    wen : in std_logic;
    rd1 : out std_logic_vector (15 downto 0);
    rd2 : out std_logic_vector (15 downto 0)
);
end component;

component seven_seg is
    Port ( Digit0 : in STD_LOGIC_VECTOR (3 downto 0);
           Digit1 : in STD_LOGIC_VECTOR (3 downto 0);
           Digit2 : in STD_LOGIC_VECTOR (3 downto 0);
           Digit3 : in STD_LOGIC_VECTOR (3 downto 0);
           CAT : out STD_LOGIC_VECTOR (6 downto 0);
           clk : in STD_LOGIC;
           AN : out STD_LOGIC_VECTOR (3 downto 0));
end component;


component rams_no_change is
    port ( clk : in std_logic;
    we : in std_logic;
    en : in std_logic;
    addr : in std_logic_vector(7 downto 0);
    di : in std_logic_vector(15 downto 0);
    do : out std_logic_vector(15 downto 0));
end component;

signal r1 : std_logic_vector (15 downto 0);
signal doubled : std_logic_vector (15 downto 0);
signal r2 : std_logic_vector (15 downto 0);
signal rp : std_logic_vector (15 downto 0);
signal reset : std_logic;
signal count_up : std_logic;
signal write_en : std_logic;

begin
    mpg1 : mpg port map(button=>btn(0), clk=>clk, enable=>d1);
    
    seg1 : seven_seg port map(Digit0=>to_display(3 downto 0), Digit1=>to_display(7 downto 4), Digit2=>to_display(11 downto 8), 
                              Digit3=>to_display(15 downto 12), cat=>CAT,clk=>clk, an=>an);

--    to_display <= rom(conv_integer(cnt));
    
    to_display <= doubled when sw(1)='1' else r1;

    doubled <= r1(14 downto 0) & '0';
    
    count_up <= d1 when sw(0)='1' else '0';
    write_en <= d1 when sw(0)='0' else '0';
    
    
    mpgreset : mpg port map(button=>btn(2), clk=>clk, enable=>reset);
    
    ram : rams_no_change port map(clk=>clk, we=>write_en, en=>'1', addr=>cnt, di=>doubled, do=>r1);

    process (clk)
    begin
        if rising_edge(clk) then
            if reset='1' then
                cnt <= "00000000";        
            end if;
            
            if count_up='1' then
                cnt <= cnt + 1;
            end if;
        end if;
    end process;
    
    led(7 downto 0) <= cnt;

end Behavioral;

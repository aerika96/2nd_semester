----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/03/2017 09:21:13 AM
-- Design Name: 
-- Module Name: mpg - Behavioral
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

entity mpg is
    Port ( button : in STD_LOGIC;
           clk : in STD_LOGIC;
           enable : out STD_LOGIC);
end mpg;

architecture Behavioral of mpg is

signal q1, q2,q3 : std_logic;
signal cnt : std_logic_vector (15 downto 0) := (others=>'0');

begin

    process (clk, button)
    begin
        if rising_edge(clk) then
            cnt <= cnt + 1;
            if cnt="1111111111111111" then
                q1 <= button;
            end if;
        end if;
    end process;
    
    process (clk, q1)
    begin
        if rising_edge(clk) then
            q2 <= q1;
        end if;
    end process;
    
    process (clk, q2)
        begin
            if rising_edge(clk) then
                q3 <= q2;
            end if;
        end process;

    enable <= q2 and (not q3);

end Behavioral;

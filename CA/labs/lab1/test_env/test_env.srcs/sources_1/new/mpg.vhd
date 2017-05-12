----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/03/2017 09:33:04 AM
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
    Port ( clk : in STD_LOGIC;
           button : in STD_LOGIC_VECTOR (3 downto 0);
           en : out STD_LOGIC);
end mpg;

architecture Behavioral of mpg is

signal int_e: std_logic:='0';
signal int_count :std_logic_vector(15 downto 0) := (others => '0');
signal int_out:std_logic_vector(2 downto 0) := (others => '0');
begin

  en <= int_out(1) and (not(int_out(0)));
    
  process(clk)
  
  begin
  if(rising_edge(clk)) then
  int_count<=int_count+1;
  if(int_count="1111111111111111")then
  int_e <= '1';
  end if;
  end if;
  end process;
  
  process (clk,int_e,button)
  
  begin
  if(rising_edge(clk)) then
    if(int_e='1') then
        int_out(2) <= (button(3) OR button(2) OR button(1) OR button(0));
    end if;
  end if;  
  end process;
  
  process (clk,int_out(2))
    
    begin
    if(rising_edge(clk)) then
      
          int_out(1) <= int_out(2);
      
    end if;  
    end process;
    
    
    process (clk,int_out(1))
      
      begin
      if(rising_edge(clk)) then
        
            int_out(0) <= int_out(1);
       
      end if;  
      end process;
end Behavioral;

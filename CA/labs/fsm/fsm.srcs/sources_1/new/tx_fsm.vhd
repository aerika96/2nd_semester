----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04/28/2017 04:20:01 AM
-- Design Name: 
-- Module Name: tx_fsm - Behavioral
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

entity tx_fsm is
  Port (
    clk: in std_logic;
    tx_dat:in std_logic_vector(7 downto 0);
    tx_en: in std_logic;
    rst: in std_logic;
    baud_en: in std_logic;
    tx:out std_logic;
    tx_rdy: out std_logic
   );
end tx_fsm;

architecture Behavioral of tx_fsm is
type state_type is (idle, start, bitt, stop);
signal state :state_type;
signal bit_cnt:std_logic_vector (3 downto 0):=(others=>'0');
signal bit_state: std_logic:='0';
begin
process(clk,baud_en,rst)
begin
    if(rising_edge(clk)) then
        if(baud_en='1') then
            if(bit_state='1') then
            bit_cnt<= bit_cnt +1;
            end if;
        end if;    
    end if; 
end process;

process(clk, rst,bit_cnt, baud_en)
begin
    if(rst='1') then
        state<=idle;
    elsif (rising_edge(clk)) then
    if(baud_en) then
        case state is
            when idle => if(tx_en='1') then state <= start; end if;
                        bit_state<='0';
            when start => state <=bitt;
                          bit_state<='0';
            when bitt => bit_state<='1';
                        if(bit_cnt<7)then state<=bitt;
                        elsif(bit_cnt=7) then state<=stop;
                        end if;
            when stop => state <= idle;            
        end case;
        end if;
    end if;    
end process;

process(state,bit_cnt)
begin
    case state is
        when idle => tx <='1';
                     tx_rdy<='1';
        when start => tx<='0';
                      tx_rdy<='0';
        when bitt => tx<=tx_dat(conv_integer(bit_cnt)); 
                     tx_rdy <='0';
        when stop => tx<='1';
                     tx_rdy<='0';                         
    end case;
end process;
end Behavioral;

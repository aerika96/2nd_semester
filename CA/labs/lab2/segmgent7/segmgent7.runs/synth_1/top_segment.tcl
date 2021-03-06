# 
# Synthesis run script generated by Vivado
# 

set_param xicom.use_bs_reader 1
set_msg_config -id {HDL 9-1061} -limit 100000
set_msg_config -id {HDL 9-1654} -limit 100000
create_project -in_memory -part xc7a35tcpg236-1

set_param project.singleFileAddWarning.threshold 0
set_param project.compositeFile.enableAutoGeneration 0
set_param synth.vivado.isSynthRun true
set_property webtalk.parent_dir C:/Users/AErika/Documents/2nd/2nd_sem/CA/labs/lab2/segmgent7/segmgent7.cache/wt [current_project]
set_property parent.project_path C:/Users/AErika/Documents/2nd/2nd_sem/CA/labs/lab2/segmgent7/segmgent7.xpr [current_project]
set_property default_lib xil_defaultlib [current_project]
set_property target_language VHDL [current_project]
set_property ip_output_repo c:/Users/AErika/Documents/2nd/2nd_sem/CA/labs/lab2/segmgent7/segmgent7.cache/ip [current_project]
set_property ip_cache_permissions {read write} [current_project]
read_vhdl -library xil_defaultlib {
  C:/Users/AErika/Documents/2nd/2nd_sem/CA/labs/lab2/segmgent7/segmgent7.srcs/sources_1/imports/new/mpg.vhd
  C:/Users/AErika/Documents/2nd/2nd_sem/CA/labs/lab2/segmgent7/segmgent7.srcs/sources_1/new/segment7.vhd
  C:/Users/AErika/Documents/2nd/2nd_sem/CA/labs/lab2/segmgent7/segmgent7.srcs/sources_1/new/top_segment.vhd
}
foreach dcp [get_files -quiet -all *.dcp] {
  set_property used_in_implementation false $dcp
}
read_xdc C:/Users/AErika/Documents/2nd/2nd_sem/CA/labs/lab1/test_env/test_env.srcs/constrs_1/new/constraints.xdc
set_property used_in_implementation false [get_files C:/Users/AErika/Documents/2nd/2nd_sem/CA/labs/lab1/test_env/test_env.srcs/constrs_1/new/constraints.xdc]


synth_design -top top_segment -part xc7a35tcpg236-1


write_checkpoint -force -noxdef top_segment.dcp

catch { report_utilization -file top_segment_utilization_synth.rpt -pb top_segment_utilization_synth.pb }

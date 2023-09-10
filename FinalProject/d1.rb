with_fx :bpf, mix:0 do
  live_loop :loop_amen do
    sample :ambi_glass_rub, rate: 0.1
    sleep 1
    sample :ambi_glass_rub, rate: 0.2
    sleep 1
    sample :ambi_glass_rub, rate: 0.3
    sleep 1
    sample :ambi_glass_rub, rate: 0.4
    sleep 1
    sample :ambi_glass_rub, rate: 0.5
    sleep 1
    sample :ambi_glass_rub, rate: 0.6
    sleep 1
    sample :ambi_glass_rub, rate: 0.7
    sleep 1
    sample :ambi_glass_rub, rate: 0.8
    sleep 1
    sample :ambi_glass_rub, rate: 0.9
    sleep 1
    sample :ambi_glass_rub, rate: -1
    sleep 1
  end
  sleep 5
  live_loop :fll do
    sample :bass_thick_c, rate: 1, amp: 2
    sleep 0.5
    sleep 0.5
  end
end

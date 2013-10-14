require 'facter'

Facter.loadfacts

puts "Processors count: #{ Facter.processorcount }"

0.upto(Facter.processorcount.to_i - 1) do |i|
    puts "Processor ##{i}: #{ Facter.send("processor#{i}") }"
end

puts "Domain: #{ Facter.domain }"

puts "IP: #{ Facter.ipaddress }"

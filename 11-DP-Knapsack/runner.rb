require "benchmark" #https://skorks.com/2010/03/timing-ruby-code-it-is-easy-with-benchmark/
require 'timeout'
require 'open3'



@solutions = [ 
  {:label => "DP-W", :file => "./_K-dpW" }, 
  {:label => "DP-W-optimized", :file => "./_K-dpW_opt" },
# {:label => "Brute-Force", :file => "./K-bf" },  
#  {:label => "Brute-Force optimized", :file => "./K-bf-opt" },
#  {:label => "Naive", :file => "./K-naive" }
]
@TLtime = 20 #seconds


#hard: ks_106_0, ks_400_0 ks_82_0 ks_300_0
#test: ks_400_0 	 time:   0.000336   0.000874 292.560596 (293.645400)
#test:  	 time:   0.000355   0.000931 101.864983 (102.347141)
#quite slow: ks_100_1, ks_200_1, ks_1000_0
#test: ks_200_1 	 time:   0.000318   0.000866  47.971731 ( 48.321986)
#ok slow ks_500_0
#test: ks_500_0 	 time:   0.000345   0.000916  10.674428 ( 10.717098)

@ls="ks_30_0		ks_lecture_dp_1	ks_19_0		ks_50_0		ks_lecture_dp_2
ks_100_0	ks_200_0	ks_40_0		ks_50_1	ks_45_0		ks_60_0
ks_100_2	ks_4_0 ks_500_0		ks_100_1		ks_200_1 ks_1000_0 ks_106_0 ks_400_0 ks_82_0 ks_300_0"



#@ls="ks_lecture_dp_1 ks_lecture_dp_2"

@tests = @ls.split(/[[[:space:]],\n,\t]+/)

@tlength = @tests.inject(0){|l,test| [l, (test).length].max }
@TestLabel = "Test"



#### Print table headers

def print_w_spaces(data, label="")

  l =  (label.is_a? Numeric) ? label : label.length
  print data
  (l-data.length).times{print " "}
  print"\t\t"    
end


################ Print params ################

@round = 3 
tmp = 111.1111111111111111
@tab = "\t\t"
@time_length = "#{@tab}#{tmp.round(@round)} sec.".length


################ Headers printing ################
puts "Time Limit is #{@TLtime} s."
puts "===========================\n\n\n"
print_w_spaces(@TestLabel, @tlength)
#(@tlength-@TestLabel.size).times{print " "}; print"\t"
@solutions.each{ |sol| print_w_spaces(sol[:label], @time_length) }
@headers_length =  @solutions.inject(@tlength+@tab.length){ |l, sol| l+=[@time_length, (sol[:label]).length+@tab.length ].max }

print "\n"
(@headers_length*(19.to_f/13)).to_i.times{print "="}
print"\n"
################ Eof Headers printing ################



@tests.each do |f|
  print_w_spaces("#{f}", @tlength)
  @solutions.each do |sol|
    @prog = sol[:file]
    @label = sol[:label]
    @TL = false
    #print "#{@label}: "
    begin
     complete_results = Timeout::timeout(@TLtime) do    
         @time = Benchmark.realtime do #.measure
            Thread.new{@stdout, @stderr, @status = Open3.capture3("cat ./K-tests/#{f} | ./#{@prog} ") }.value  
        end
      end
    rescue  Timeout::Error
        @TL = true        
    end
    if !@TL
      File.open("./log/#{f}.log", 'w+') { |file| file.write(@stdout) }    
       print_w_spaces("#{@time.round(@round)} sec.", [@label.length, @time_length].max)      
    else
      print_w_spaces( "TL", [@label.length, @time_length].max)      
    end        
  end
  print "\n"
  (@headers_length*(19.to_f/13)).to_i.times{print "-"}
  print"\n"
  
end
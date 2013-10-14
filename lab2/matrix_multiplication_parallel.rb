# require 'rinda' - included in Ruby stdlib by default
# require 'parallel'
require 'peach'

def matrix_multiply(a, b)
    if a.transpose.size != b.size
        throw "Could not multiply matrices with incompatible row/column counts"
    end

=begin
    res = []
    n = a.transpose.size

    a.each_with_index do |a_row, a_ri|
        res_row = []

        b.transpose.each_with_index do |b_col, b_ci|
            elts = []

            0.upto(n - 1) { |i| elts << a_row[i] * b_col[i] }

            puts ">> [#{ a_ri + 1 }, #{ b_ci + 1 }] = [#{ elts.join ' + ' }]"

            res_row << elts.inject(:+)
        end

        res << res_row
    end

    res
=end

    num_threads = a.size

    # Parallel.map(a, :in_processes => num_threads) do |ar|
    a.pmap(num_threads) do |ar|
        b.map do |bc|
            ar.zip(bc).map {|x,y| x*y}.inject {|z,w| z+w}
        end
    end
end

a_rows, a_cols = rand(1000), rand(1000)
b_rows, b_cols = a_cols, rand(1000)

a, b = [], []

a_rows.times { tmp = []; a_cols.times { tmp << (rand(500) - 250) }; a << tmp }
b_rows.times { tmp = []; b_cols.times { tmp << (rand(500) - 250) }; b << tmp }

=begin
a = [
        [1, 2, 3],
        [2, -1, 2],
    ]

b = [
        [3, 2, 1],
        [1, 3, -2],
        [2, 4, 2]
    ]
=end

c = matrix_multiply(a, b)

puts "#{ a_rows }x#{ a_cols } MUL #{ b_rows }x#{ b_cols }"

#puts c.inspect
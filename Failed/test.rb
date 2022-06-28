
width  = 10
height = 10
seed   = (ARGV[2] || rand(0xFFFF_FFFF)).to_i

srand(seed)

grid = Array.new(height) { Array.new(width, 0) }

# --------------------------------------------------------------------
# 2. Set up constants to aid with describing the passage directions
# --------------------------------------------------------------------

S, E = 1, 2
HORIZONTAL, VERTICAL = 1, 2

# --------------------------------------------------------------------
# 3. Helper routines
# --------------------------------------------------------------------

def display_maze(grid)
  # print "\e[H" # move to upper-left
  puts " " + "_" * (grid[0].length * 2 - 1)
  grid.each_with_index do |row, y|
    print "|"
    row.each_with_index do |cell, x|
      bottom = y+1 >= grid.length
      south  = (cell & S != 0 || bottom)
      south2 = (x+1 < grid[y].length && grid[y][x+1] & S != 0 || bottom)
      east   = (cell & E != 0 || x+1 >= grid[y].length)

      print(south ? "_" : " ")
      print(east ? "|" : ((south && south2) ? "_" : " "))
    end
    puts
  end
end

def choose_orientation(width, height)
  if width < height
    HORIZONTAL
  elsif height < width
    VERTICAL
  else
    rand(2) == 0 ? HORIZONTAL : VERTICAL
  end
end

# --------------------------------------------------------------------
# 4. The recursive-division algorithm itself
# --------------------------------------------------------------------

def divide(grid, x, y, width, height, orientation)
  return if width < 2 || height < 2

  # display_maze(grid)
  sleep 0.02

  horizontal = orientation == HORIZONTAL

  # where will the wall be drawn from?
  wx = x + (horizontal ? 0 : rand(width-2))
  wy = y + (horizontal ? rand(height-2) : 0)

  # where will the passage through the wall exist?
  px = wx + (horizontal ? rand(width) : 0)
  py = wy + (horizontal ? 0 : rand(height))

  # what direction will the wall be drawn?
  dx = horizontal ? 1 : 0
  dy = horizontal ? 0 : 1

  # how long will the wall be?
  length = horizontal ? width : height

  # what direction is perpendicular to the wall?
  dir = horizontal ? S : E

  length.times do
    grid[wy][wx] |= dir if wx != px || wy != py
    message = "X: #{wx} Y: #{wy} // #{px},#{py}" 
    puts message 
    wx += dx
    wy += dy
  end
  display_maze(grid)
  nx, ny = x, y
  w, h = horizontal ? [width, wy-y+1] : [wx-x+1, height]
  divide(grid, nx, ny, w, h, choose_orientation(w, h))

  nx, ny = horizontal ? [x, wy+1] : [wx+1, y]
  w, h = horizontal ? [width, y+height-wy-1] : [x+width-wx-1, height]
  divide(grid, nx, ny, w, h, choose_orientation(w, h))
end

print "\e[2J" # clear screen

divide(grid, 0, 0, width, height, choose_orientation(width, height))
display_maze(grid)

# --------------------------------------------------------------------
# 5. Show the parameters used to build this maze, for repeatability
# --------------------------------------------------------------------

# puts "#{$0} #{width} #{height} #{seed}"
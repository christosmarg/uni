#!/usr/libexec/flua

-- Usage: caller.lua <inline_low> <inline_high>

-- Read the inline function boundaries from the command line arguments
local inl_lo = tonumber(arg[1])
local inl_hi = tonumber(arg[2])

-- Split string by line
local function magiclines(s)
        if s:sub(-1)~="\n" then s=s.."\n" end
        return s:gmatch("(.-)\n")
end

-- Read stdin line by line
for line in magiclines(io.read("*a")) do
	local cols = {}
	local sym_lo = {}
	local sym_hi = {}

	-- Only match FUNC (i.e., function) symbols
	if string.find(line, "FUNC") then
		-- Split each line into columns
		for s in string.gmatch(line, "([^ ]+)") do
			cols[#cols + 1] = s
		end

		-- Calculate the symbol's lower and upper boundaries
		sym_lo = tonumber(cols[2], 16)
		sym_hi = tonumber(cols[2], 16) + tonumber(cols[3], 10)
		
		-- See if the inline function is inlined within current symbol
		if sym_lo <= inl_lo and inl_hi <= sym_hi then
			print(cols[#cols])
			print("\tsym_lo=\t", string.format("0x%x", sym_lo))
			print("\tsym_hi=\t", string.format("0x%x", sym_hi))
			print("\tinl_lo=\t", string.format("0x%x", inl_lo))
			print("\tinl_hi=\t", string.format("0x%x", inl_hi))
		end
	end
end

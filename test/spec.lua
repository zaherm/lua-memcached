local M = {}
M.__index = M
setmetatable(M, {
  __index = function(t, k)
    print("lol")
  end
})

function M.new()
  local m = {}
  setmetatable(m, M)
  m.tests = {}
  return m
end

function M.exists(file)
  local f = io.open(file, "rb")
  if f then f:close() end
  return f ~= nil
end

function M.readlines(file)
  if not M.exists(file) then return {} end
  local lines = {}
  for line in io.lines(file) do
    lines[#lines + 1] = line
  end
  return lines
end

-- http://lua-users.org/wiki/SplitJoin
function M.split(str, pat)
   local t = {}  -- NOTE: use {n = 0} in Lua-5.0
   local fpat = "(.-)" .. pat
   local last_end = 1
   local s, e, cap = str:find(fpat, 1)
   while s do
      table.insert(t,cap)
      last_end = e+1
      s, e, cap = str:find(fpat, last_end)
   end
   if last_end <= #str then
      cap = str:sub(last_end)
      table.insert(t, cap)
   end
   return t
end

function M:describe(desc, func, before, after)
  self.tests[#self.tests + 1] = {
    desc = desc,
    func = func
  }
end

function M:set(key, value)
  self[key] = value
end

function M:get(key)
  return self[key]
end

function M:execute(index, test)
  local reports = {}
  local function report(text, result)
    reports[#reports + 1] = { text = text, result = result }
  end
  local ok, err = pcall(test.func, report)
  return { desc = test.desc, result = ok and "pass" or "fail", err = not ok and err or nil, reports = reports }
end

function M:report(results)
  print("> spec results: ")
  for i, res in ipairs(results) do
    print("\t- spec["..tostring(i).."] "..tostring(res.desc).." result='"..res.result.."' err='"..tostring(res.err).."'")
    if res.reports then
      for j, r in ipairs(res.reports) do
        print("\t\t > spec["..tostring(r.text).."] result='"..tostring(r.result and "pass" or "fail").."'")
      end
    end
  end
end

function M:run()
  local ok
  local results = {}
  for i, s in ipairs(self.tests) do
    results[i] = self:execute(i, s)
  end
  self:report(results)
end

return M

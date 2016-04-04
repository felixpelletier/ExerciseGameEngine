local state = require('state')
state.changecontext('link', {arcana='Aeon', level='1', angle='0'})

state.input('select')
processinput()

print("\nState")
for key, value in pairs(state) do print(key, value) end
print("\nContext")
for key, value in pairs(state.context) do print(key, value) end

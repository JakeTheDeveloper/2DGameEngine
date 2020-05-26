window = { Title = "2D", Width = 1500, Height = 1100 }

function AddStuff(a, b)
    print("[LUA] AddStuff("..a..","..b..") called \n")
    return a + b
end

function DoThing(a, b)
    print("[LUA] DoThing("..a..","..b..") called \n")

    c = HostFunction(a + 10,b * 3)

    return c;
end
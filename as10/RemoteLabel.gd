extends Label

var second = 1
var counter = 0

func updateValue(newValue, senderID = 1):    
	if !(is_multiplayer_authority() or senderID == 0):
		updateValueRPC.rpc_id(1, newValue, multiplayer.get_unique_id())
		return
		
	counter = newValue
	text = "Counter: " + String.num(counter)
	
	# Make sure the value change gets propigated to all of the clients! 
	if is_multiplayer_authority() and senderID != 0:
		print(senderID, " has set the value to: ", counter)
		updateValueRPC.rpc(newValue, 0)

@rpc("any_peer")
func updateValueRPC(newValue, senderID):
	if is_multiplayer_authority() or senderID == 0:
		updateValue(newValue, senderID)

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	if !is_multiplayer_authority(): return
	
	second -= delta
	if second < 0:
		second = 1
		counter += 1
		updateValue(counter + 0)
		text = "Counter: " + str(counter)
	pass
	
	
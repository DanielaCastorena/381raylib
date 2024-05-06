extends Control

@onready var game = $"../Game"
@onready var address_entry = $PanelContainer/VBoxContainer/IPAddress
@onready var label = $"../Game/Label"

const PORT = 9999
var peer = ENetMultiplayerPeer.new()

# Called when the node enters the scene tree for the first time.
func buttonCommon():
	hide()
	game.show()

func _on_host_button_pressed():
	buttonCommon()
	
	peer.create_server(PORT)
	multiplayer.multiplayer_peer = peer
	multiplayer.peer_connected.connect(addPlayer)
	multiplayer.peer_disconnected.connect(removePlayer)
	
func _on_join_button_pressed():
	buttonCommon()
	
	peer.create_client(address_entry.text, PORT)
	multiplayer.multiplayer_peer = peer
	
func addPlayer(peer_id):
	print(peer_id)
	pass
	
func removePlayer(peer_id):
	print("ded")
	
# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

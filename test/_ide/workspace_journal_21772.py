# 2025-05-06T20:43:29.704416600
import vitis

client = vitis.create_client()
client.set_workspace(path="test")

comp = client.get_component(name="hls_test")
comp.run(operation="C_SIMULATION")

comp.run(operation="SYNTHESIS")


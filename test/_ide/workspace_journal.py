# 2025-05-27T19:47:06.746763
import vitis

client = vitis.create_client()
client.set_workspace(path="test")

comp = client.get_component(name="hls_test")
comp.run(operation="C_SIMULATION")

comp.run(operation="C_SIMULATION")

comp.run(operation="C_SIMULATION")

comp.run(operation="C_SIMULATION")

comp.run(operation="C_SIMULATION")

comp.run(operation="SYNTHESIS")

vitis.dispose()


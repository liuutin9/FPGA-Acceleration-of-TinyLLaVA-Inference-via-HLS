# 2025-05-27T00:31:45.052833
import vitis

client = vitis.create_client()
client.set_workspace(path="test")

comp = client.get_component(name="hls_test")
comp.run(operation="C_SIMULATION")

comp.run(operation="C_SIMULATION")

comp.run(operation="C_SIMULATION")

comp.run(operation="C_SIMULATION")

comp.run(operation="SYNTHESIS")

comp.run(operation="IMPLEMENTATION")

vitis.dispose()


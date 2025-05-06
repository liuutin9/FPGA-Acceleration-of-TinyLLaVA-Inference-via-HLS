# 2025-05-06T19:27:09.950949200
import vitis

client = vitis.create_client()
client.set_workspace(path="test")

comp = client.get_component(name="hls_test")
comp.run(operation="C_SIMULATION")

comp.run(operation="SYNTHESIS")

comp.run(operation="CO_SIMULATION")

comp.run(operation="PACKAGE")

comp.run(operation="IMPLEMENTATION")

comp.run(operation="IMPLEMENTATION")

status = client.export_projects(components = ["hls_test"], system_projects = [], include_build_dir = False, dest = "C:\Users\liuut\Desktop\archive.zip")

vitis.dispose()


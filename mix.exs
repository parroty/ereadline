defmodule Ereadline.Mixfile do
  use Mix.Project

  def project do
    [app: :ereadline,
     version: "0.0.1",
     language: :erlang,
     deps: deps]
  end

  def application do
    [applications: [], mod: {:ereadline, []}]
  end

  defp deps do
    []
  end
end
